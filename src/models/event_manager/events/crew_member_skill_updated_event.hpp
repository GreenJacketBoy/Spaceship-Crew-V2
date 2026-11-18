#ifndef CREW_MEMBER_SKILL_UPDATED_EVENT_HPP
#define CREW_MEMBER_SKILL_UPDATED_EVENT_HPP

#include "event_template.hpp"
#include "skill.hpp"

struct CrewMemberSkillUpdatedPayload {
    const size_t crewMemberId;
    const SkillType skillType;
    const size_t newLevel;
    const size_t previousLevel;
};

class CrewMemberSkillUpdatedSubscriber {
public: 
    virtual void handleCrewMemberSkillUpdated(CrewMemberSkillUpdatedPayload &payload) = 0;
};

class CrewMemberSkillUpdatedEvent : public Event<CrewMemberSkillUpdatedPayload, CrewMemberSkillUpdatedSubscriber> {
public:
    void emitEvent(CrewMemberSkillUpdatedPayload &payload) override;
};

#endif // !CREW_MEMBER_SKILL_UPDATED_EVENT_HPP
