#include "room_list_model.hpp"

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
                case IdRole: return this->qVariantSizeT(room->getId());
                case NameRole: return QVariant(room->getName().c_str());
                case CrewCapacityRole: return this->qVariantSizeT(room->getCrewCapacity());
                case StorageCapacityRole: return this->qVariantSizeT(room->getStorageCapacity());
                case SizeRole: return this->qVariantSizeT(room->getSize());
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

/** Because QVariant doesn't have a constructor for size_t */
constexpr QVariant RoomListModel::qVariantSizeT(const size_t number) const {
    QVariant qVariant;
    qVariant.setValue(number);
    return qVariant;
}
