#include "get_room.hpp"
#include "room.hpp"
#include "game_state.hpp"
#include <stdexcept>

std::optional<Room *> util::getRoom(size_t roomId) noexcept {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return std::optional<Room *>();

    try {
        auto &room = spaceship.get()->value().getRoomMap().at(roomId);
        if (!room) return std::optional<Room *>();
        return std::optional<Room *>(room.get());
    } catch (std::out_of_range) {
        return std::optional<Room *>();
    }
}
