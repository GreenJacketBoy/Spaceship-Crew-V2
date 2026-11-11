#ifndef ROOM_SIZE_UPDATED_EVENT_HPP
#define ROOM_SIZE_UPDATED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>

struct RoomSizeUpdatedPayload {
    const size_t roomId;
    const size_t size;
};

class RoomSizeUpdatedSubscriber {
public: 
    virtual void handleRoomSizeUpdated(RoomSizeUpdatedPayload &payload) = 0;
};

class RoomSizeUpdatedEvent : public Event<RoomSizeUpdatedPayload, RoomSizeUpdatedSubscriber> {
public:
    void emitEvent(RoomSizeUpdatedPayload &payload) override;
};

#endif // !ROOM_SIZE_UPDATED_EVENT_HPP
