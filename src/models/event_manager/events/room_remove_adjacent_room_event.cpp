#include "room_remove_adjacent_room_event.hpp"
#include "room.hpp"
#include "get_room.hpp"

void RoomRemoveAdjacentRoomEvent::emitEvent(RoomRemoveAdjacentRoomPayload &payload) {
    auto optionalRoom = util::getRoom(payload.roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();
    bool wasRemovedFromFirst = room->removeAdjacentRoom(payload.adjacentRoomId);

    auto optionalAdjacentRoom = util::getRoom(payload.adjacentRoomId);
    if (!optionalAdjacentRoom) return;
    auto adjacentRoom = optionalAdjacentRoom.value();
    bool wasRemovedFromSecond = adjacentRoom->removeAdjacentRoom(payload.roomId);

    if (!wasRemovedFromFirst && !wasRemovedFromSecond) return;

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomRemoveAdjacentRoom(payload);
    }
}
