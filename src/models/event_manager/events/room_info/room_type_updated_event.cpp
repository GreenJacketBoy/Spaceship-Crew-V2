#include "room_type_updated_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomTypeUpdatedEvent::emitEvent(RoomTypeUpdatedPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();
    room->setRoomType(payload.type);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomTypeUpdated(payload);
    }
}
