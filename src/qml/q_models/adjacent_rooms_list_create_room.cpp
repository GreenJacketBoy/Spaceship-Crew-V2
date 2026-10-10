#include "adjacent_rooms_list_create_room.hpp"
#include "get_room.hpp"
#include "q_variant_special_type.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <qabstractitemmodel.h>
#include <qvariant.h>

int AdjacentRoomsListCreateRoomModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

int AdjacentRoomsListCreateRoomModel::rowCount(const QModelIndex &parent) const {
    return this->adjacentRooms.size();
}

QVariant AdjacentRoomsListCreateRoomModel::data(const QModelIndex &index, int role) const {
    std::optional<size_t> roomId;

    size_t i = 0;
    for (auto &roomIdFromSet : this->adjacentRooms) {
        if (i == index.row()) {
            roomId = roomIdFromSet;
            break;
        }
        i++;
    }

    if (!roomId) {
        std::cout << "Warning in AdjacentRoomsListCreateRoomModel : adjacent room set out of bounds\n";
        return QVariant();
    }

    auto optionalRoom = util::getRoom(roomId.value());
    if (!optionalRoom) return QVariant();
    Room *room = optionalRoom.value();

    switch (role) {
        case IdRole: return util::qVariantSizeT(room->getId());
        case NameRole: return QVariant(room->getName().c_str());
        case TypeRole: return QVariant(room->getTypeName());
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> AdjacentRoomsListCreateRoomModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { TypeRole, "type"},
    };
}

void AdjacentRoomsListCreateRoomModel::adjacentRoomAddedCreateForm(size_t roomId) {
    if (this->adjacentRooms.contains(roomId)) return;

    this->layoutAboutToBeChanged();
    this->adjacentRooms.push_back(roomId);
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void AdjacentRoomsListCreateRoomModel::adjacentRoomRemovedCreateForm(size_t roomId) {
    this->layoutAboutToBeChanged();
    this->adjacentRooms.removeOne(roomId);
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}
