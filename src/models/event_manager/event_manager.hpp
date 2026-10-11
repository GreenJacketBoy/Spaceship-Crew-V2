#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "create_crew_member_event.hpp"
#include "create_room_event.hpp"
class EventManager {
public: 
    CreateRoomEvent &getCreateRoomEvent() { return this->createRoomEvent; }
    CreateCrewMemberEvent &getCreateCrewMemberEvent() { return this->createCrewMemberEvent; }

private:
    CreateRoomEvent createRoomEvent;
    CreateCrewMemberEvent createCrewMemberEvent;
};

#endif // !EVENT_MANAGER_HPP
