#include "get_crew_member.hpp"
#include "crew_member.hpp"
#include "game_state.hpp"
#include <optional>
#include <stdexcept>

std::optional<CrewMember *> util::getCrewMember(size_t crewMemberId) noexcept {
    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship == nullptr || !spaceship.get()->has_value()) return std::nullopt;

    try {
        auto &crewMember = spaceship.get()->value().getCrewMap().at(crewMemberId);
        if (!crewMember) return std::nullopt;
        return std::optional<CrewMember *>(crewMember.get());
    } catch (std::out_of_range) {
        return std::nullopt;
    }
}
