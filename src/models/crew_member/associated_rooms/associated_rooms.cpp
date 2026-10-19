#include "associated_rooms.hpp"
#include <optional>
#include "crew_member_moved_event.hpp"

void AssociatedRooms::handleCrewMemberMoved(CrewMemberMovedPayload &payload) {
    this->currentRoom = payload.toRoomId;
};
