#include "crew_member.hpp"
#include "get_crew_list.hpp"
#include "game_state.hpp"

std::optional<std::map<size_t, std::unique_ptr<CrewMember>> *> util::getCrewList() noexcept {
    using optionalCrewList = std::optional<std::map<size_t, std::unique_ptr<CrewMember>> *>;

    auto &spaceship = GameState::getInstance().getSpaceShip();
    if (spaceship.get() == nullptr || !spaceship.get()->has_value()) return optionalCrewList();

    return optionalCrewList(&spaceship.get()->value().getCrewMap());
}
