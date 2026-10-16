#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "create_crew_member_event.hpp"
#include "create_room_event.hpp"
#include "room_selected_event.hpp"
class EventManager {
public: 
    inline CreateRoomEvent &getCreateRoomEvent() { return this->createRoomEvent; }
    inline CreateCrewMemberEvent &getCreateCrewMemberEvent() { return this->createCrewMemberEvent; }
    inline RoomSelectedEvent &getRoomSelectedEvent() { return this->roomSelectedEvent; }
private:
    CreateRoomEvent createRoomEvent;
    CreateCrewMemberEvent createCrewMemberEvent;
    RoomSelectedEvent roomSelectedEvent;
};

#endif // !EVENT_MANAGER_HPP
