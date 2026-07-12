#ifndef ENGINEERING_EVENT_H
#define ENGINEERING_EVENT_H

#include "crew_member.hpp"
#include "event.hpp"
#include "room.hpp"
#include "skill.hpp"
#include <cstddef>

class EngineeringEvent : public Event {
public:
    EngineeringEvent(size_t roomId) {
        this->type = EventType::ENGINEERING;
        this->typeName = "Engineering Event";

        this->roomId = roomId;
    }

    inline size_t getRoomId() { return this->roomId; }
    
    bool repair(CrewMember &engineer, Room &roomToRepair) {
        if (engineer.getSkillLevel(SkillType::ENGINEERING) < requiredSkill.level) {
            return false;
        }

        // TODO : implement repair
        return true;
    }

protected:
    size_t roomId = -1;
    Skill requiredSkill = { SkillType::ENGINEERING, 1 };
};

#endif // !ENGINEERING_EVENT_H
