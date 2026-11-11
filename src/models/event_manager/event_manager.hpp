#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "room_crew_capacity_updated_event.hpp"
#include "room_name_updated_event.hpp"
#include "room_size_updated_event.hpp"
#include "room_storage_capacity_updated_event.hpp"
#include "room_type_updated_event.hpp"
#include "create_crew_member_event.hpp"
#include "create_room_event.hpp"
#include "crew_member_moved_event.hpp"
#include "crew_member_selected_event.hpp"
#include "room_selected_event.hpp"
#include "crew_member_name_updated_event.hpp"
#include "crew_member_title_updated_event.hpp"

class EventManager {
public: 
    inline CreateRoomEvent &getCreateRoomEvent() { return this->createRoomEvent; }
    inline CreateCrewMemberEvent &getCreateCrewMemberEvent() { return this->createCrewMemberEvent; }
    inline RoomSelectedEvent &getRoomSelectedEvent() { return this->roomSelectedEvent; }
    inline CrewMemberMovedEvent &getCrewMemberMovedEvent() { return this->crewMemberMovedEvent; }
    inline CrewMemberSelectedEvent &getCrewMemberSelectedEvent() { return this->crewMemberSelectedEvent; }
    inline CrewMemberNameUpdatedEvent &getCrewMemberNameUpdatedEvent() { return this->crewMemberNameUpdatedEvent; }
    inline CrewMemberTitleUpdatedEvent &getCrewMemberTitleUpdatedEvent() { return this->crewMemberTitleUpdatedEvent; }
    inline RoomNameUpdatedEvent &getRoomNameUpdatedEvent() { return this->roomNameUpdatedEvent; }
    inline RoomTypeUpdatedEvent &getRoomTypeUpdatedEvent() { return this->roomTypeUpdatedEvent; }
    inline RoomSizeUpdatedEvent &getRoomSizeUpdatedEvent() { return this->roomSizeUpdatedEvent; }
    inline RoomCrewCapacityUpdatedEvent &getRoomCrewCapacityUpdatedEvent() { return this->roomCrewCapacityUpdatedEvent; }
    inline RoomStorageCapacityUpdatedEvent &getRoomStorageCapacityUpdatedEvent() { return this->roomStorageCapacityUpdatedEvent; }
 
private:
    CreateRoomEvent createRoomEvent;
    CreateCrewMemberEvent createCrewMemberEvent;
    RoomSelectedEvent roomSelectedEvent;
    CrewMemberMovedEvent crewMemberMovedEvent;
    CrewMemberSelectedEvent crewMemberSelectedEvent;
    CrewMemberNameUpdatedEvent crewMemberNameUpdatedEvent;
    CrewMemberTitleUpdatedEvent crewMemberTitleUpdatedEvent;
    RoomNameUpdatedEvent roomNameUpdatedEvent;
    RoomTypeUpdatedEvent roomTypeUpdatedEvent;
    RoomSizeUpdatedEvent roomSizeUpdatedEvent;
    RoomCrewCapacityUpdatedEvent roomCrewCapacityUpdatedEvent;
    RoomStorageCapacityUpdatedEvent roomStorageCapacityUpdatedEvent;
};

#endif // !EVENT_MANAGER_HPP
