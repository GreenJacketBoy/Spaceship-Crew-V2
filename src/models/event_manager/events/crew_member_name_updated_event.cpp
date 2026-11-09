#include "crew_member_name_updated_event.hpp"
#include "get_crew_member.hpp"
#include "crew_member.hpp"

void CrewMemberNameUpdatedEvent::emitEvent(CrewMemberNameUpdatedPayload &payload) {
    auto optionalCrewMember = util::getCrewMember(payload.crewMemberId);
    if (!optionalCrewMember) return;
    auto crewMember = optionalCrewMember.value();
    crewMember->setName(std::string(payload.name));

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberNameUpdated(payload);
    }
}
