#include "room_crew_capacity_updated_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomCrewCapacityUpdatedEvent::emitEvent(RoomCrewCapacityUpdatedPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();
    room->setCrewCapacity(payload.crewCapacity);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomCrewCapacityUpdated(payload);
    }
}
