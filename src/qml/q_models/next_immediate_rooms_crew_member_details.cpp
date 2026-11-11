#include "next_immediate_rooms_crew_member_details.hpp"
#include "crew_member_moved_event.hpp"
#include "get_crew_member.hpp"
#include "index_of.hpp"
#include "q_variant_special_type.hpp"
#include "room.hpp"
#include "get_room.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <optional>
#include <qdebug.h>
#include <qvariant.h>

int NextImmediateRoomsCrewMemberDetailsModel::rowCount(const QModelIndex &parent) const {
    auto optionalCurrentRoom = this->getCurrentRoom();
    if (!optionalCurrentRoom) return 0;

    return optionalCurrentRoom.value()->getAdjacentRooms().size();
}

QVariant NextImmediateRoomsCrewMemberDetailsModel::data(const QModelIndex &index, int role) const {
    auto optionalCurrentRoom = this->getCurrentRoom();
    if (!optionalCurrentRoom) return QVariant();

    auto &adjacentRooms = optionalCurrentRoom.value()->getAdjacentRooms();

    auto optionalRoomIdAtIndex = util::atIndex(adjacentRooms, index.row());
    if (!optionalRoomIdAtIndex) return QVariant();
    auto optionalRoomAtIndex = util::getRoom(*optionalRoomIdAtIndex.value());
    if (!optionalRoomAtIndex) return QVariant();
    auto roomAtIndex = optionalRoomAtIndex.value();

    switch (role) {
        case IdRole: return util::qVariantSizeT(roomAtIndex->getId());
        case NameRole: return QVariant(roomAtIndex->getName().c_str());
        case CrewCapacityRole: return util::qVariantSizeT(roomAtIndex->getCrewCapacity());
        case StorageCapacityRole: return util::qVariantSizeT(roomAtIndex->getStorageCapacity());
        case SizeRole: return util::qVariantSizeT(roomAtIndex->getSize());
        case TypeRole: return QVariant(roomAtIndex->getTypeName());
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> NextImmediateRoomsCrewMemberDetailsModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { CrewCapacityRole, "crewCapacity"},
        { StorageCapacityRole, "storageCapacity"},
        { SizeRole, "size"},
        { TypeRole, "type"},
    };
}

void NextImmediateRoomsCrewMemberDetailsModel::handleRoomCreated(size_t &roomId) {
    auto optionalCurrentRoom = this->getCurrentRoom();
    if (!optionalCurrentRoom) return;
    if (!optionalCurrentRoom.value()->isRoomAdjacent(roomId)) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

constexpr std::optional<Room *> NextImmediateRoomsCrewMemberDetailsModel::getCurrentRoom() const {
    if (!this->crewMemberId) return std::nullopt;
    auto optionalCrewMember = util::getCrewMember(this->crewMemberId.value());
    if (!optionalCrewMember) return std::nullopt;
    auto optionalCurrentRoomId = optionalCrewMember.value()->getCurrentRoomId();
    if (!optionalCurrentRoomId) return std::nullopt;

    return util::getRoom(optionalCurrentRoomId.value());
}

void NextImmediateRoomsCrewMemberDetailsModel::handleCrewMemberMoved(CrewMemberMovedPayload &payload) {
    if (payload.toRoomId) {
        auto optionalRoom = util::getRoom(payload.toRoomId.value());
        if (!optionalRoom) return;
    }

    this->layoutAboutToBeChanged();
    this->crewMemberId = payload.crewMemberId;
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void NextImmediateRoomsCrewMemberDetailsModel::handleCrewMemberSelected(size_t &crewMemberId) {
    this->layoutAboutToBeChanged();
    this->crewMemberId = crewMemberId;
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void NextImmediateRoomsCrewMemberDetailsModel::handleRoomNameUpdated(RoomNameUpdatedPayload &payload) {
    this->updateDataForRoom(payload.roomId);
}

void NextImmediateRoomsCrewMemberDetailsModel::handleRoomTypeUpdated(RoomTypeUpdatedPayload &payload) {
    this->updateDataForRoom(payload.roomId);
}

constexpr void NextImmediateRoomsCrewMemberDetailsModel::updateDataForRoom(const size_t roomId) {
    auto optionalCurrentRoom = this->getCurrentRoom();
    if (!optionalCurrentRoom) return;
    auto &adjacentRooms = optionalCurrentRoom.value()->getAdjacentRooms();

    auto optionalIndex = util::indexOf<size_t>(adjacentRooms, roomId);
    if (!optionalIndex) return;
    size_t index = optionalIndex.value();

    this->dataChanged(this->index(index, 0), this->index(index, 0));
}

void NextImmediateRoomsCrewMemberDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberMovedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomNameUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomTypeUpdatedEvent().subscribe(*this);
}
