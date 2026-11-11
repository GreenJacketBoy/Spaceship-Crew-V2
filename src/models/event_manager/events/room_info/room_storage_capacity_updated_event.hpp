#ifndef ROOM_STORAGE_CAPACITY_UPDATED_EVENT_HPP
#define ROOM_STORAGE_CAPACITY_UPDATED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>

struct RoomStorageCapacityUpdatedPayload {
    const size_t roomId;
    const size_t crewCapacity;
};

class RoomStorageCapacityUpdatedSubscriber {
public: 
    virtual void handleRoomStorageCapacityUpdated(RoomStorageCapacityUpdatedPayload &payload) = 0;
};

class RoomStorageCapacityUpdatedEvent : public Event<RoomStorageCapacityUpdatedPayload, RoomStorageCapacityUpdatedSubscriber> {
public:
    void emitEvent(RoomStorageCapacityUpdatedPayload &payload) override;
};

#endif // !ROOM_STORAGE_CAPACITY_UPDATED_EVENT_HPP
