#ifndef MEDICAL_EVENT_H
#define MEDICAL_EVENT_H

#include "crew_member.hpp"
#include "event.hpp"
#include "skill.hpp"
#include <cstddef>

class MedicalEvent : public Event {
public:
    MedicalEvent(size_t crewMemberId) {
        this->type = EventType::MEDICAL;
        this->typeName = "Medical Event";

        this->crewMemberId = crewMemberId;
    }

    inline size_t getCrewMemberId() { return this->crewMemberId; }
    
    bool heal(CrewMember &healer, CrewMember &patient) {
        if (healer.getSkillLevel(SkillType::MEDICAL) < requiredSkill.level) {
            return false;
        }

        // TODO : implement health for crew members
        return true;
    }

protected:
    size_t crewMemberId = -1;
    Skill requiredSkill = { SkillType::MEDICAL, 1 };
};

#endif // !MEDICAL_EVENT_H
