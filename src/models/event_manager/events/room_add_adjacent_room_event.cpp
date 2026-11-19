#include "room_add_adjacent_room_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomAddAdjacentRoomEvent::emitEvent(RoomAddAdjacentRoomPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;

    auto optionalAdjacentRoom = util::getRoom(payload.adjacentRoomId);
    if (!optionalAdjacentRoom) return;

    bool wasAddedToFirst = optionalRoom.value()->addAdjacentRoom(payload.adjacentRoomId);
    bool wasAddedToSecond = optionalAdjacentRoom.value()->addAdjacentRoom(payload.roomId);

    if (!wasAddedToFirst && !wasAddedToSecond) return;

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomAddAdjacentRoom(payload);
    }
}
