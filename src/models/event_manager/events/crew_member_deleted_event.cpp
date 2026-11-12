#include "crew_member_deleted_event.hpp"
#include "get_crew_list.hpp"
#include "crew_member.hpp"
#include "get_crew_member.hpp"
#include "room.hpp"
#include "get_room.hpp"

void CrewMemberDeletedEvent::emitEvent(CrewMemberDeletedPayload &payload) {
    auto optionalCrewList = util::getCrewList();
    if (!optionalCrewList) return;
    auto crewList = optionalCrewList.value();

    auto node = crewList->extract(payload.deletedCrewMemberId);
    if (node.empty()) return;
    auto &crewMember = node.mapped();
    if (!crewMember) return;

    if (payload.deletedCrewMemberCurrentRoomId) {
        auto optionalCurrentRoom = util::getRoom(payload.deletedCrewMemberCurrentRoomId.value());
        if (!optionalCurrentRoom) optionalCurrentRoom.value()->handleCrewMemberDeleted(payload);
    }

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberDeleted(payload);
    }
}

void CrewMemberDeletedEvent::deleteCrewMember(size_t crewMemberId) {
    auto optionalCrewMember = util::getCrewMember(crewMemberId);
    if (!optionalCrewMember) return;
    auto crewMember = optionalCrewMember.value();

    CrewMemberDeletedPayload payload = {crewMemberId, crewMember->getCurrentRoomId()};
    this->emitEvent(payload);
}
