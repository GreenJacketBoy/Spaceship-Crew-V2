#include "room_storage_capacity_updated_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomStorageCapacityUpdatedEvent::emitEvent(RoomStorageCapacityUpdatedPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();
    room->setStorageCapacity(payload.crewCapacity);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomStorageCapacityUpdated(payload);
    }
}
