#include "at_index.hpp"
#include "crew_member.hpp"
#include "crew_list_model.hpp"
#include "game_state.hpp"
#include "get_crew_list.hpp"
#include "q_variant_special_type.hpp"

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

    switch (role) {
        case IdRole: return util::qVariantSizeT(crewMember->getId());
        case NameRole: return QVariant(crewMember->getName().c_str());
        case TitleRole: return QVariant(crewMember->getTitle().c_str());
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> CrewListModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { TitleRole, "title"},
    };
}

void CrewListModel::handleCrewMemberCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void CrewListModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateCrewMemberEvent().subscribe(*this);
}
