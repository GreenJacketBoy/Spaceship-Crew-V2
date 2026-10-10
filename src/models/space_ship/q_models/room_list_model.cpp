#include "room_list_model.hpp"
#include "game_state.hpp"
#include "get_room_list.hpp"
#include "q_variant_special_type.hpp"

int RoomListModel::columnCount(const QModelIndex &parent) const {
    auto roomList = util::getRoomList();
    if (!roomList) return 0;
    return 1;
}

int RoomListModel::rowCount(const QModelIndex &parent) const {
    auto roomList = util::getRoomList();
    if (!roomList) return 0;
    return roomList.value()->size();
}

QVariant RoomListModel::data(const QModelIndex &index, int role) const {
    auto roomList = util::getRoomList();
    if (!roomList) return QVariant();
    size_t i = 0;
    for (auto &[_, room] : *roomList.value()) {
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

void RoomListModel::handleRoomCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void RoomListModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
}
