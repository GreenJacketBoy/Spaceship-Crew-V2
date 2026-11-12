#include "selected_crew_member_id.hpp"
#include "index_of.hpp"
#include "at_index.hpp"
#include "crew_member.hpp"
#include "crew_list_model.hpp"
#include "game_state.hpp"
#include "get_crew_list.hpp"
#include "q_variant_special_type.hpp"
#include <cstddef>
#include <qlogging.h>

int CrewListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

int CrewListModel::rowCount(const QModelIndex &parent) const {
    auto crewList = util::getCrewList();
    if (!crewList) return 0;
    return crewList.value()->size();
}

QVariant CrewListModel::data(const QModelIndex &index, int role) const {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return QVariant();
    auto optionalCrewMember = util::atIndex(*optionalCrewList.value(), index.row());
    if (!optionalCrewMember || !optionalCrewMember.value()) return QVariant();
    auto crewMember = optionalCrewMember.value()->get();
    const auto selectedCrewMemberId = util::selectedCrewMemberId();

    switch (role) {
        case IdRole: return util::qVariantSizeT(crewMember->getId());
        case NameRole: return QVariant(crewMember->getName().c_str());
        case TitleRole: return QVariant(crewMember->getTitle().c_str());
        case IsSelectedRole: return QVariant(selectedCrewMemberId && selectedCrewMemberId.value() == crewMember->getId());
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> CrewListModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { TitleRole, "title"},
        { IsSelectedRole, "isSelected"},
    };
}

void CrewListModel::handleCrewMemberCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void CrewListModel::handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void CrewListModel::handleCrewMemberSelected(size_t &crewMemberId) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto roomList = optionalCrewList.value();

    std::optional<size_t> currentSelectedIndex;
    std::optional<size_t> toBeSelectedIndex;

    size_t index = 0;
    for (const auto &[_, crewMember] : *roomList) {
        if (crewMember->getId() == crewMemberId) toBeSelectedIndex = index;
        if (this->lastSelectedCrewMemberId && crewMember->getId() == this->lastSelectedCrewMemberId.value()) currentSelectedIndex = index;
        if ((currentSelectedIndex || !this->lastSelectedCrewMemberId) && toBeSelectedIndex) break;
        index++;
    }

    this->lastSelectedCrewMemberId = crewMemberId;
    if (currentSelectedIndex)
        this->dataChanged(this->index(currentSelectedIndex.value(), 0), this->index(currentSelectedIndex.value(), 0));
    if (toBeSelectedIndex)
        this->dataChanged(this->index(toBeSelectedIndex.value(), 0), this->index(toBeSelectedIndex.value(), 0));
}

void CrewListModel::handleCrewMemberUnselected(size_t &crewMemberId) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto crewList = optionalCrewList.value();

    std::optional<size_t> selectedIndex = util::indexOf<size_t>(*crewList, crewMemberId);
    
    if (selectedIndex)
        this->dataChanged(this->index(selectedIndex.value(), 0), this->index(selectedIndex.value(), 0));
}

void CrewListModel::handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto crewList = optionalCrewList.value();

    auto optionalIndex = util::indexOf<size_t>(*crewList, payload.crewMemberId);
    if (!optionalIndex) return;
    size_t index = optionalIndex.value();
    this->dataChanged(this->index(index, 0), this->index(index, 0));
}

void CrewListModel::handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto crewList = optionalCrewList.value();

    auto optionalIndex = util::indexOf<size_t>(*crewList, payload.crewMemberId);
    if (!optionalIndex) return;
    size_t index = optionalIndex.value();
    this->dataChanged(this->index(index, 0), this->index(index, 0));
}

void CrewListModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateCrewMemberEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberNameUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberTitleUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberDeletedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberUnselectedEvent().subscribe(*this);
}
