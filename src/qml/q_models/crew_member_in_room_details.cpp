#include "selected_room_id.hpp"
#include "index_of.hpp"
#include "get_crew_list.hpp"
#include "crew_member_in_room_details.hpp"
#include "get_crew_member.hpp"
#include "q_variant_special_type.hpp"
#include "get_room.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <qvariant.h>

int CrewMemberInRoomDetailsModel::rowCount(const QModelIndex &parent) const {
    auto optionalRoom = util::getRoom(util::selectedRoomId());
    if (!optionalRoom) return 0;
    return optionalRoom.value()->getCrewMembersInRoom().size();
}

QVariant CrewMemberInRoomDetailsModel::data(const QModelIndex &index, int role) const {
    auto optionalRoom = util::getRoom(util::selectedRoomId());
    if (!optionalRoom) return QVariant();
    auto &crewMembersInRoom = optionalRoom.value()->getCrewMembersInRoom();

    auto optionalCrewMemberIdAtIndex = util::atIndex(crewMembersInRoom, index.row());
    if (!optionalCrewMemberIdAtIndex) return QVariant();
    auto optionalCrewMemberAtIndex = util::getCrewMember(*optionalCrewMemberIdAtIndex.value());
    if (!optionalCrewMemberAtIndex) return QVariant();
    auto crewMember = optionalCrewMemberAtIndex.value();

    switch (role) {
        case IdRole: return util::qVariantSizeT(crewMember->getId());
        case NameRole: return QVariant(crewMember->getName().c_str());
        case TitleRole: return QVariant(crewMember->getTitle().c_str());
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> CrewMemberInRoomDetailsModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { TitleRole, "title"},
    };
}

void CrewMemberInRoomDetailsModel::handleCrewMemberMoved(CrewMemberMovedPayload &payload) {
    const auto optionalSelectedRoomId = util::selectedRoomId();
    if (!optionalSelectedRoomId) return;
    const size_t selectedRoomId = optionalSelectedRoomId.value();

    if (!payload.toRoomId && !payload.fromRoomId) return;
    if (payload.toRoomId && payload.toRoomId.value() != selectedRoomId) return;
    if (payload.fromRoomId && payload.fromRoomId.value() != selectedRoomId) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void CrewMemberInRoomDetailsModel::handleRoomSelected(size_t &roomId) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void CrewMemberInRoomDetailsModel::handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto crewList = optionalCrewList.value();

    auto optionalIndex = util::indexOf<size_t>(*crewList, payload.crewMemberId);
    if (!optionalIndex) return;
    size_t index = optionalIndex.value();
    this->dataChanged(this->index(index, 0), this->index(index, 0));
}

void CrewMemberInRoomDetailsModel::handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto crewList = optionalCrewList.value();

    auto optionalIndex = util::indexOf<size_t>(*crewList, payload.crewMemberId);
    if (!optionalIndex) return;
    size_t index = optionalIndex.value();
    this->dataChanged(this->index(index, 0), this->index(index, 0));
}

void CrewMemberInRoomDetailsModel::handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId) return;
    if (!payload.deletedCrewMemberCurrentRoomId) return;
    if (selectedRoomId.value() != payload.deletedCrewMemberCurrentRoomId.value()) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void CrewMemberInRoomDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCrewMemberMovedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberTitleUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberNameUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberDeletedEvent().subscribe(*this);
}
