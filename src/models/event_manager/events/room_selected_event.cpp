#include "room_selected_event.hpp"
#include "game_state.hpp"
#include "selected_room_id.hpp"

void RoomSelectedEvent::emitEvent(size_t &roomId) {
    GameState::getInstance().getSelectedEntitiesMap()->handleRoomSelected(roomId);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomSelected(roomId);
    }
}

void RoomSelectedEvent::selectRoom(size_t roomId) {
    const auto selectedRoomId = util::selectedRoomId();
    bool isAlreadySelected = selectedRoomId && selectedRoomId.value() == roomId;

    if (isAlreadySelected) GameState::getInstance().getEventManager()->getRoomUnselectedEvent().emitEvent(roomId);
    else this->emitEvent(roomId);
}
