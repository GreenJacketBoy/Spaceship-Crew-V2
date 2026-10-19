#include "at_index.hpp"
#include "current_room_model.hpp"
#include "game_state.hpp"
#include "get_room_list.hpp"
#include "q_variant_special_type.hpp"
#include <cstddef>
#include <optional>
#include <qvariant.h>

int CurrentRoomModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

int CurrentRoomModel::rowCount(const QModelIndex &parent) const {
    auto roomMap = util::getRoomList();
    if (!roomMap) return 1;

    return roomMap.value()->size() + 1; // + 1 for the null option
}

QVariant CurrentRoomModel::data(const QModelIndex &index, int role) const {
    if (index.row() == 0) {
        switch (role) {
            case Text: return QVariant("None");
            case Value: return util::QVariantSpecialType(std::optional<size_t>());
        }
        return QVariant();
    }

    auto optionalRoomMap = util::getRoomList();
    if (!optionalRoomMap) return QVariant();
    auto roomMap = optionalRoomMap.value();


    size_t i = 0;
    auto optionalRoom = util::atIndex(*roomMap, index.row() - 1);
    if (!optionalRoom || !optionalRoom.value()) return QVariant();
    auto room = optionalRoom.value()->get();

    switch (role) {
        case Text: return QVariant(std::format("#{} {} ({})", room->getId(), room->getName(), room->getTypeName()).c_str());
        case Value: return util::QVariantSpecialType(std::optional<size_t>(room->getId()));
    }

    return QVariant();
}

QHash<int, QByteArray> CurrentRoomModel::roleNames() const {
    return {
        { Text, "text"},
        { Value, "value"},
    };
}

void CurrentRoomModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
}

void CurrentRoomModel::handleRoomCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(1, 2), this->index(this->rowCount()-1, 2));
    this->layoutChanged();
}
