#include "room_deleted_event.hpp"
#include "get_room_list.hpp"
#include "get_room_list.hpp"
#include "room.hpp"
#include "get_room.hpp"
#include <cstddef>

void RoomDeletedEvent::emitEvent(size_t &roomId) {
    auto optionalRoomList = util::getRoomList();
    if (!optionalRoomList) return;
    auto roomList = optionalRoomList.value();

    auto node = roomList->extract(roomId);
    if (node.empty()) return;
    auto &room = node.mapped();
    if (!room) return;

    room->handleRoomDeleted(roomId);

    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomDeleted(roomId);
    }
}

void RoomDeletedEvent::deleteRoom(size_t roomId) {
    this->emitEvent(roomId);
}
