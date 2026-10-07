#include "room_list_model.hpp"
#include "game_state.hpp"
#include "q_variant_special_type.hpp"
#include <iostream>
#include <optional>
#include <qabstractitemmodel.h>

int RoomListModel::columnCount(const QModelIndex &parent) const {
    if (!this->roomList) return 0;
    return 1;
}

int RoomListModel::rowCount(const QModelIndex &parent) const {
    if (!this->roomList) return 0;
    return this->roomList.value()->size();
}

QVariant RoomListModel::data(const QModelIndex &index, int role) const {
    if (!this->roomList.has_value()) return QVariant();
    size_t i = 0;
    for (auto &[_, room] : *this->roomList.value()) {
        if (index.row() == i) {
            switch (role) {
                case IdRole: return util::qVariantSizeT(room->getId());
                case NameRole: return QVariant(room->getName().c_str());
                case CrewCapacityRole: return util::qVariantSizeT(room->getCrewCapacity());
                case StorageCapacityRole: return util::qVariantSizeT(room->getStorageCapacity());
                case SizeRole: return util::qVariantSizeT(room->getSize());
                case TypeRole: return QVariant(room->getTypeName());
                default: return QVariant();
            }
        }
        i++;
    }
    return QVariant();
}

QHash<int, QByteArray> RoomListModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { CrewCapacityRole, "crewCapacity"},
        { StorageCapacityRole, "storageCapacity"},
        { SizeRole, "size"},
        { TypeRole, "type"},
    };
}

void RoomListModel::setRoomList(std::map<size_t, std::unique_ptr<Room>> &roomList) {
    this->roomList = &roomList;
}

void RoomListModel::handleRoomCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));

    this->layoutChanged();
}

void RoomListModel::TEMPORARY_subscribeToUpdates() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
}
