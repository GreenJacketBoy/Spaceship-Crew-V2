#include "crew_member.hpp"
#include "skill.hpp"
#include <iostream>

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

    std::cout << "Crew Member of name " << this->name << " and title " << this->title << " has been created\n";
    if (skills.size() > 0) std::cout << "Skills :\n";
    for (auto &skill : skills) {
        std::cout << " - " << getSkillName(skill.type) << " level " << skill.level << "\n";
    }
}
