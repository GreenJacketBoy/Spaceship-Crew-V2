#ifndef ROOM_ADD_ADJACENT_ROOM_EVENT_HPP
#define ROOM_ADD_ADJACENT_ROOM_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>

struct RoomAddAdjacentRoomPayload {
    const size_t roomId;
    const size_t adjacentRoomId;
};

class RoomAddAdjacentRoomSubscriber {
public: 
    virtual void handleRoomAddAdjacentRoom(RoomAddAdjacentRoomPayload &payload) = 0;
};

class RoomAddAdjacentRoomEvent : public Event<RoomAddAdjacentRoomPayload, RoomAddAdjacentRoomSubscriber> {
public:
    void emitEvent(RoomAddAdjacentRoomPayload &payload) override;
};

#endif // !ROOM_ADD_ADJACENT_ROOM_EVENT_HPP
