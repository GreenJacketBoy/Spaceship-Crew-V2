#include "crew_member.hpp"

CrewMember::CrewMember(
    std::string &&name,
    std::string &&title,
    const std::vector<Skill> &skills
): 
name(name), 
title(title) 
{
    this->id = this->next_id;
    this->next_id++;

    this->skills = std::map<SkillType, size_t>();
    for(auto skill : skills) {
        this->setSkillLevel(skill.type, skill.level);
    }
}
