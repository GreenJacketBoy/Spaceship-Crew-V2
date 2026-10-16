#include "room_selected_event.hpp"

void RoomSelectedEvent::emitEvent(size_t &roomId) {
    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomSelected(roomId);
    }
}
