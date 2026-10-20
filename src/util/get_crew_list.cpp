#include "crew_member.hpp"
#include "get_crew_list.hpp"
#include "game_state.hpp"
#include <optional>

std::optional<std::map<size_t, std::unique_ptr<CrewMember>> *> util::getCrewList() noexcept {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return std::nullopt;

    return &spaceship.get()->value().getCrewMap();
}
