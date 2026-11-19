#ifndef ROOM_REMOVE_ADJACENT_ROOM_EVENT_HPP
#define ROOM_REMOVE_ADJACENT_ROOM_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>

struct RoomRemoveAdjacentRoomPayload {
    const size_t roomId;
    const size_t adjacentRoomId;
};

class RoomRemoveAdjacentRoomSubscriber {
public: 
    virtual void handleRoomRemoveAdjacentRoom(RoomRemoveAdjacentRoomPayload &payload) = 0;
};

class RoomRemoveAdjacentRoomEvent : public Event<RoomRemoveAdjacentRoomPayload, RoomRemoveAdjacentRoomSubscriber> {
public:
    void emitEvent(RoomRemoveAdjacentRoomPayload &payload) override;
};

#endif // !ROOM_SIZE_UPDATED_EVENT_HPP
