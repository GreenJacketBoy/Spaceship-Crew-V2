#ifndef ROOM_NAME_UPDATED_EVENT_HPP
#define ROOM_NAME_UPDATED_EVENT_HPP

#include "event_template.hpp"

struct RoomNameUpdatedPayload {
    const size_t roomId;
    const char *name;
};

class RoomNameUpdatedSubscriber {
public: 
    virtual void handleRoomNameUpdated(RoomNameUpdatedPayload &payload) = 0;
};

class RoomNameUpdatedEvent : public Event<RoomNameUpdatedPayload, RoomNameUpdatedSubscriber> {
public:
    void emitEvent(RoomNameUpdatedPayload &payload) override;
};

#endif // !ROOM_NAME_UPDATED_EVENT_HPP
