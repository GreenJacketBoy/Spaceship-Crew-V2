#ifndef ROOM_CREW_CAPACITY_UPDATED_EVENT_HPP
#define ROOM_CREW_CAPACITY_UPDATED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>

struct RoomCrewCapacityUpdatedPayload {
    const size_t roomId;
    const size_t crewCapacity;
};

class RoomCrewCapacityUpdatedSubscriber {
public: 
    virtual void handleRoomCrewCapacityUpdated(RoomCrewCapacityUpdatedPayload &payload) = 0;
};

class RoomCrewCapacityUpdatedEvent : public Event<RoomCrewCapacityUpdatedPayload, RoomCrewCapacityUpdatedSubscriber> {
public:
    void emitEvent(RoomCrewCapacityUpdatedPayload &payload) override;
};

#endif // !ROOM_CREW_CAPACITY_UPDATED_EVENT_HPP
