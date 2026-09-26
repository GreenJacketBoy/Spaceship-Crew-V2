#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "create_room_event.hpp"
class EventManager {
public: 
    CreateRoomEvent &getCreateRoomEvent() { return createRoomEvent; }

private:
    CreateRoomEvent createRoomEvent;
};

#endif // !EVENT_MANAGER_HPP
