#include "skills_lookup.hpp"
#include "crew_member.hpp"
#include "game_state.hpp"
#include "get_crew_list.hpp"
#include "get_crew_member.hpp"
#include "skill.hpp"
#include <cstddef>
#include <optional>
#include <stdexcept>

const SkillLevelToCrewMemberIds_Map &SkillsLookup::getConstSkillMap(SkillType skillType) {
    return this->getSkillMap(skillType);
}

void SkillsLookup::setSkillLevel(size_t crewMemberId, SkillType skillType, size_t level) {
    if (level == 0) return; // TODO: log a warning
    SkillLevelToCrewMemberIds_Map  &skillMap = this->getSkillMap(skillType);
    try {
        auto &crewMemberIds = skillMap.at(level);
        crewMemberIds.insert(crewMemberId);
    } catch (std::out_of_range) {
        skillMap.insert({level, {crewMemberId}});
    }
}

void SkillsLookup::removeSkillLevel(size_t crewMemberId, SkillType skillType, size_t previousLevel) {
    SkillLevelToCrewMemberIds_Map  &skillMap = this->getSkillMap(skillType);
    try {
        auto &crewMemberIds = skillMap.at(previousLevel);
        crewMemberIds.erase(crewMemberId);
        if (crewMemberIds.empty()) skillMap.erase(previousLevel);
    } catch (std::out_of_range) {
        // TODO: log a warning
    }
}

std::optional<CrewMember *> SkillsLookup::getFreeCrewMember_EqualOrAbove(SkillType skillType, size_t level) {
    // TODO randomized the selection
    if (level == 0) {
        auto optionalCrewList = util::getCrewList();
        if (!optionalCrewList) return std::nullopt;
        for (auto &[_, crewMember] : *optionalCrewList.value()) {
            if (crewMember) crewMember.get();
        }
        return std::nullopt;
    }
    SkillLevelToCrewMemberIds_Map  &skillMap = this->getSkillMap(skillType);
    
    try {
        auto &crewMemberIds = skillMap.at(level);
        for (size_t id : crewMemberIds) {
            auto optionalCrewMember = util::getCrewMember(id);
            if (optionalCrewMember) return optionalCrewMember; // TODO: check if crew member is free
        }
        throw std::out_of_range("skill map contained the level, but none of its crew ids were valid");
    } catch (std::out_of_range) {
        for (auto &[currentLevel, crewMemberIds] : skillMap) {
            if (currentLevel < level) continue;
            for (size_t id : crewMemberIds) {
                auto optionalCrewMember = util::getCrewMember(id);
                if (optionalCrewMember) return optionalCrewMember; // TODO: check if crew member is free
            }
        }
        return std::nullopt;
    }
}

void SkillsLookup::handleCrewMemberCreated(size_t &crewMemberId) {
    auto optionalCrewMember = util::getCrewMember(crewMemberId);
    if (!optionalCrewMember) return;
    
    for (auto &[skillType, level] : optionalCrewMember.value()->getSkills()) {
        this->setSkillLevel(crewMemberId, skillType, level);
    }
}

void SkillsLookup::handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) {
    for (auto &[skillType, level] : payload.skills) {
        this->removeSkillLevel(payload.deletedCrewMemberId, skillType, level);
    }
}

void SkillsLookup::handleCrewMemberSkillUpdated(CrewMemberSkillUpdatedPayload &payload) {
    if (payload.newLevel != 0) this->setSkillLevel(payload.crewMemberId, payload.skillType, payload.newLevel);
    if (payload.previousLevel != 0) this->removeSkillLevel(payload.crewMemberId, payload.skillType, payload.previousLevel);
}

constexpr SkillLevelToCrewMemberIds_Map &SkillsLookup::getSkillMap(SkillType skillType) {
    switch (skillType) {
        case SkillType::ENGINEERING: return this->engineeringMap;
        case SkillType::MEDICAL: return this->medicalMap;
        case SkillType::PILOTING: return this->pilotingMap;
        default: throw no_skill_map_for_this_skill_type();
    }
}
