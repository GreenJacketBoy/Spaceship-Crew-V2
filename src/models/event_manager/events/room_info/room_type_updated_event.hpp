#ifndef ROOM_TYPE_UPDATED_EVENT_HPP
#define ROOM_TYPE_UPDATED_EVENT_HPP

#include "event_template.hpp"
#include "room_type.hpp"

struct RoomTypeUpdatedPayload {
    const size_t roomId;
    const RoomType &type;
};

class RoomTypeUpdatedSubscriber {
public: 
    virtual void handleRoomTypeUpdated(RoomTypeUpdatedPayload &payload) = 0;
};

class RoomTypeUpdatedEvent : public Event<RoomTypeUpdatedPayload, RoomTypeUpdatedSubscriber> {
public:
    void emitEvent(RoomTypeUpdatedPayload &payload) override;
};

#endif // !ROOM_TYPE_UPDATED_EVENT_HPP
