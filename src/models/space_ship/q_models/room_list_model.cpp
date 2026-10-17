#include "room_list_model.hpp"
#include "game_state.hpp"
#include "get_room.hpp"
#include "get_room_list.hpp"
#include "q_variant_special_type.hpp"
#include <cstddef>
#include <optional>

int RoomListModel::columnCount(const QModelIndex &parent) const {
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
                case IsSelectedRole: return QVariant(this->selectedRoomId && this->selectedRoomId.value() == room->getId());
                default: return QVariant(); // TODO: log a warning
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
        { IsSelectedRole, "isSelected"},
    };
}

void RoomListModel::handleRoomCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void RoomListModel::handleRoomSelected(size_t &roomId) {
    auto optionalRoomList = util::getRoomList();
    if (!optionalRoomList) return;
    auto roomList = optionalRoomList.value();

    std::optional<size_t> currentSelectedIndex;
    std::optional<size_t> toBeSelectedIndex;

    size_t index = 0;
    for (const auto &[_, room] : *roomList) {
        if (room->getId() == roomId) toBeSelectedIndex = index;
        if (this->selectedRoomId && room->getId() == this->selectedRoomId.value()) currentSelectedIndex = index;
        if ((currentSelectedIndex || !this->selectedRoomId) && toBeSelectedIndex) break;
        index++;
    }

    this->selectedRoomId = roomId;
    if (currentSelectedIndex)
        this->dataChanged(this->index(currentSelectedIndex.value(), 0), this->index(currentSelectedIndex.value(), 0));
    if (toBeSelectedIndex)
        this->dataChanged(this->index(toBeSelectedIndex.value(), 0), this->index(toBeSelectedIndex.value(), 0));
}

void RoomListModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
}
