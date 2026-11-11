#include "room_name_updated_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomNameUpdatedEvent::emitEvent(RoomNameUpdatedPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();
    room->setName(std::string(payload.name));

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomNameUpdated(payload);
    }
}
