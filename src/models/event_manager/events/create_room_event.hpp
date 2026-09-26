#ifndef CREATE_ROOM_EVENT_HPP
#define CREATE_ROOM_EVENT_HPP

#include "event_template.hpp"

class Room; // Forward declaration. 
// I'm putting a comment because it's the first time I use it, and I'll cringe in a year because it's obvious it is.
// :sunglasses_hiding_tears:

class CreateRoomSubscriber {
public: 
    virtual void handleRoomCreated(Room &payload) = 0;
};

class CreateRoomEvent : public Event<Room, CreateRoomSubscriber> {
public:
    virtual void emit(Room &payload) {
        for (auto subscriber : this->subscribers) {
            subscriber->handleRoomCreated(payload);
        }
    }
};

#endif // !CREATE_ROOM_EVENT_HPP
