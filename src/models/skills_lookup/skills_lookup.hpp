#ifndef SKILLS_LOOKUP_HPP
#define SKILLS_LOOKUP_HPP

#include <exception>
#include <cstddef>
#include <map>
#include <optional>
#include <unordered_set>
#include "create_crew_member_event.hpp"
#include "crew_member.hpp"
#include "crew_member_deleted_event.hpp"
#include "crew_member_skill_updated_event.hpp"
#include "skill.hpp"

using SkillLevelToCrewMemberIds_Map = std::map<size_t, std::unordered_set<size_t>>;
class no_skill_map_for_this_skill_type : public std::exception {};

class CrewMember;

class SkillsLookup : public CreateCrewMemberSubscriber, public CrewMemberDeletedSubscriber, public CrewMemberSkillUpdatedSubscriber {
public: 
    const SkillLevelToCrewMemberIds_Map &getConstSkillMap(SkillType skillType);

    void setSkillLevel(size_t crewMemberId, SkillType skillType, size_t level);

    void removeSkillLevel(size_t crewMemberId, SkillType skillType, size_t previousLevel);

    std::optional<CrewMember *> getFreeCrewMember_EqualOrAbove(SkillType skillType, size_t level);

    void handleCrewMemberCreated(size_t &payload);

    void handleCrewMemberDeleted(CrewMemberDeletedPayload &payload);

    void handleCrewMemberSkillUpdated(CrewMemberSkillUpdatedPayload &payload);

    // currently, all events handler methods are called directly in the emitEvent method of the event, since this class 
    // is a source of truth on which other subscribers may rely
    void triggerSubscriptions() = delete; 

private:
    constexpr SkillLevelToCrewMemberIds_Map &getSkillMap(SkillType skillType);

    SkillLevelToCrewMemberIds_Map medicalMap;
    SkillLevelToCrewMemberIds_Map engineeringMap;
    SkillLevelToCrewMemberIds_Map pilotingMap;
};

#endif // !SKILLS_LOOKUP_HPP
