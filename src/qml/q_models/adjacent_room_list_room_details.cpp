#include "adjacent_room_list_room_details.hpp"
#include "q_variant_special_type.hpp"
#include "room.hpp"
#include "get_room.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include <qvariant.h>

int AdjacentRoomListRoomDetailsModel::columnCount(const QModelIndex &parent) const {
    return 3;
}

int AdjacentRoomListRoomDetailsModel::rowCount(const QModelIndex &parent) const {
    if (!this->roomId) return 0;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return 0;
    return optionalRoom.value()->getAdjacentRooms().size();
}

QVariant AdjacentRoomListRoomDetailsModel::data(const QModelIndex &index, int role) const {
    if (!this->roomId) return QVariant();
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return QVariant();
    auto &adjacentRooms = optionalRoom.value()->getAdjacentRooms();

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
    if (!this->roomId) return;
    auto selectedRoomId = this->roomId.value();
    auto optionalCreatedRoom = util::getRoom(roomId);
    if (!optionalCreatedRoom) return;
    if (!optionalCreatedRoom.value()->isRoomAdjacent(selectedRoomId)) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void AdjacentRoomListRoomDetailsModel::handleRoomSelected(size_t &roomId) {
    auto optionalRoom = util::getRoom(roomId);
    if (!optionalRoom) return;

    this->layoutAboutToBeChanged();
    this->roomId = roomId;
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void AdjacentRoomListRoomDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
}
