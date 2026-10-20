#include "get_room_list.hpp"
#include "room.hpp"
#include "game_state.hpp"

std::optional<std::map<size_t, std::unique_ptr<Room>> *> util::getRoomList() noexcept {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return std::nullopt;

    return &spaceship.get()->value().getRoomMap();
}
