#ifndef SELECTED_CREW_MEMBER_ID_HPP
#define SELECTED_CREW_MEMBER_ID_HPP

#include "game_state.hpp"
#include <cstddef>
#include <optional>

namespace util {
    inline const std::optional<size_t> selectedCrewMemberId() {
        return GameState::getInstance().getSelectedEntitiesMap()->getCrewMemberId();
    }
}

#endif // !SELECTED_CREW_MEMBER_ID_HPP
