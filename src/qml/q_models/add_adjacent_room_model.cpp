#include "add_adjacent_room_model.hpp"
#include "game_state.hpp"
#include "q_variant_special_type.hpp"
#include <cstddef>
#include <format>
#include <qvariant.h>

int AddAdjacentRoomModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

int AddAdjacentRoomModel::rowCount(const QModelIndex &parent) const {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return 0;

    // yeah this won't work when I have multi-threading, but as I like to say, problem for later
    return spaceship.get()->value().getRoomMap().size();
}

QVariant AddAdjacentRoomModel::data(const QModelIndex &index, int role) const {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return QVariant();

    auto &roomMap = spaceship.get()->value().getRoomMap();

    size_t i = 0;
    for (const auto &[_, room] : roomMap) {
        if (index.row() != i) {
            i++;
            continue;
        }
        if (!room) return QVariant();

        switch (role) {
            case Text: return QVariant(std::format("#{} {} ({})", room->getId(), room->getName(), room->getTypeName()).c_str());
            case Value: return util::qVariantSizeT(room->getId());
        }
    }

    return QVariant();
}

QHash<int, QByteArray> AddAdjacentRoomModel::roleNames() const {
    return {
        { Text, "text"},
        { Value, "value"},
    };
}

void AddAdjacentRoomModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateRoomEvent().subscribe(*this);
}

void AddAdjacentRoomModel::handleRoomCreated(size_t &payload) {
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}
