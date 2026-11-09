#include "crew_member_title_updated_event.hpp"
#include "get_crew_member.hpp"
#include "crew_member.hpp"

void CrewMemberTitleUpdatedEvent::emitEvent(CrewMemberTitleUpdatedPayload &payload) {
    auto optionalCrewMember = util::getCrewMember(payload.crewMemberId);
    if (!optionalCrewMember) return;
    auto crewMember = optionalCrewMember.value();
    crewMember->setTitle(std::string(payload.title));

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberTitleUpdated(payload);
    }
}
