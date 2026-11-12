#include "room_unselected_event.hpp"
#include "game_state.hpp"

void RoomUnselectedEvent::emitEvent(size_t &roomId) {
    GameState::getInstance().getSelectedEntitiesMap()->handleRoomUnselected(roomId);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomUnselected(roomId);
    }
}
