#include "crew_member_skill_updated_event.hpp"
#include "game_state.hpp"
#include "get_crew_member.hpp"
#include "crew_member.hpp"

void CrewMemberSkillUpdatedEvent::emitEvent(CrewMemberSkillUpdatedPayload &payload) {
    auto optionalCrewMember = util::getCrewMember(payload.crewMemberId);
    if (!optionalCrewMember) return;
    auto crewMember = optionalCrewMember.value();
    crewMember->setSkillLevel(payload.skillType, payload.newLevel);

    GameState::getInstance().getSkillsLookup()->handleCrewMemberSkillUpdated(payload);

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberSkillUpdated(payload);
    }
}
