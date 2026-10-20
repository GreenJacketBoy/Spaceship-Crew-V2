#include "get_room.hpp"
#include "room.hpp"
#include "game_state.hpp"
#include <optional>
#include <stdexcept>

std::optional<Room *> util::getRoom(size_t roomId) noexcept {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return std::nullopt;

    try {
        auto &room = spaceship.get()->value().getRoomMap().at(roomId);
        if (!room) return std::nullopt;
        return room.get();
    } catch (std::out_of_range) {
        return std::nullopt;
    }
}
