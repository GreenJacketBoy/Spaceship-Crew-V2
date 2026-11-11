#include "room_size_updated_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomSizeUpdatedEvent::emitEvent(RoomSizeUpdatedPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();
    room->setSize(payload.size);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomSizeUpdated(payload);
    }
}
