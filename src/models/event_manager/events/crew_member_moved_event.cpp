#include "crew_member_moved_event.hpp"
#include "get_crew_member.hpp"
#include "crew_member.hpp"
#include "get_room.hpp"
#include "room.hpp"

void CrewMemberMovedEvent::emitEvent(CrewMemberMovedPayload &payload) {
    auto optionalCrewMember = util::getCrewMember(payload.crewMemberId);
    if (!optionalCrewMember) return; // TODO: log a warning

    optionalCrewMember.value()->getAssociatedRooms().handleCrewMemberMoved(payload);

    if (payload.toRoomId) {
        auto optionalToRoom = util::getRoom(payload.toRoomId.value());
        if (optionalToRoom) optionalToRoom.value()->handleCrewMemberMoved(payload);
    }
    if (payload.fromRoomId) {

        auto optionalFromRoom = util::getRoom(payload.fromRoomId.value());
        if (optionalFromRoom) optionalFromRoom.value()->handleCrewMemberMoved(payload);
    }
}
