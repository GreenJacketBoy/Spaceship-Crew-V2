#include "adjacent_room_list_room_details.hpp"
#include "q_variant_special_type.hpp"
#include "room.hpp"
#include "get_room.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include "selected_room_id.hpp"
#include <cstddef>
#include <qvariant.h>

int AdjacentRoomListRoomDetailsModel::rowCount(const QModelIndex &parent) const {
    auto optionalRoom = util::getRoom(util::selectedRoomId());
    if (!optionalRoom) return 0;
    return optionalRoom.value()->getAdjacentRooms().size();
}

QVariant AdjacentRoomListRoomDetailsModel::data(const QModelIndex &index, int role) const {
    auto optionalRoom = util::getRoom(util::selectedRoomId());
    if (!optionalRoom) return QVariant();
    const auto &adjacentRooms = optionalRoom.value()->getAdjacentRooms();

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

QHash<int, QByteArray> AdjacentRoomListRoomDetailsModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { CrewCapacityRole, "crewCapacity"},
        { StorageCapacityRole, "storageCapacity"},
        { SizeRole, "size"},
        { TypeRole, "type"},
    };
}

void AdjacentRoomListRoomDetailsModel::handleRoomCreated(size_t &roomId) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId) return;

    auto optionalCreatedRoom = util::getRoom(roomId);
    if (!optionalCreatedRoom) return;
    if (!optionalCreatedRoom.value()->isRoomAdjacent(selectedRoomId.value())) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void AdjacentRoomListRoomDetailsModel::handleRoomSelected(size_t &roomId) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}


void AdjacentRoomListRoomDetailsModel::handleRoomDeleted(size_t &roomId) {
    auto optionalCreatedRoom = util::getRoom(util::selectedRoomId());
    if (!optionalCreatedRoom) return;
    if (!optionalCreatedRoom.value()->isRoomAdjacent(roomId)) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void AdjacentRoomListRoomDetailsModel::handleRoomAddAdjacentRoom(RoomAddAdjacentRoomPayload &payload) {
    const auto optionalSelectedRoomId = util::selectedRoomId();
    if (!optionalSelectedRoomId) return;
    size_t selectedRoomId = optionalSelectedRoomId.value();

    if (payload.roomId != selectedRoomId && payload.adjacentRoomId != selectedRoomId) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void AdjacentRoomListRoomDetailsModel::handleRoomRemoveAdjacentRoom(RoomRemoveAdjacentRoomPayload &payload) {
    const auto optionalSelectedRoomId = util::selectedRoomId();
    if (!optionalSelectedRoomId) return;
    size_t selectedRoomId = optionalSelectedRoomId.value();

    if (payload.roomId != selectedRoomId && payload.adjacentRoomId != selectedRoomId) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void AdjacentRoomListRoomDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomDeletedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomAddAdjacentRoomEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomRemoveAdjacentRoomEvent().subscribe(*this);
}
