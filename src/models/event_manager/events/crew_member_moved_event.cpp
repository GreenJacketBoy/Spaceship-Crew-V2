#include "crew_member_moved_event.hpp"
#include "get_crew_member.hpp"
#include "crew_member.hpp"
#include "get_room.hpp"
#include "room.hpp"

void CrewMemberMovedEvent::emitEvent(CrewMemberMovedPayload &payload) {
    auto optionalCrewMember = util::getCrewMember(payload.crewMemberId);
    if (!optionalCrewMember) return; // TODO: log a warning

    optionalCrewMember.value()->getAssociatedRooms().handleCrewMemberMoved(payload);

    auto optionalToRoom = util::getRoom(payload.toRoomId);
    if (optionalToRoom) optionalToRoom.value()->handleCrewMemberMoved(payload);

    auto optionalFromRoom = util::getRoom(payload.fromRoomId);
    if (optionalFromRoom) optionalFromRoom.value()->handleCrewMemberMoved(payload);

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberMoved(payload);
    }
}
