#ifndef SELECTED_ROOM_ID_HPP
#define SELECTED_ROOM_ID_HPP

#include "game_state.hpp"
#include <cstddef>
#include <optional>

namespace util {
    inline const std::optional<size_t> selectedRoomId() {
        return GameState::getInstance().getSelectedEntitiesMap()->getRoomId();
    }
}

#endif // !SELECTED_ROOM_ID_HPP
