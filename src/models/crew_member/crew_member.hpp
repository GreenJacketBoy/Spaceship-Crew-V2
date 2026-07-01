#ifndef CREW_MEMBER_HPP
#define CREW_MEMBER_HPP

#include <map>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include "skill.hpp"

class CrewMember {
public: 
    CrewMember(
        std::string &&name,
        std::string &&title,
        const std::vector<Skill> &skills
    );

    inline size_t             getId()     { return this->id;     }
    inline const std::string &getName()   { return this->name;   }
    inline const std::string &getTitle()  { return this->title;  }
    inline const auto        &getSkills() { return this->skills; }

    inline void setName(std::string &&name)   { this->name  = name;  }
    inline void setTitle(std::string &&title) { this->title = title; }

    inline size_t getSkillLevel(const SkillType &skill) {
        try { return this->skills.at(skill); }
        catch (const std::out_of_range&) { return 0; }
    };

    inline void setSkillLevel(SkillType skill, size_t level) {
        if (level == 0) this->skills.erase(skill);
        else this->skills.insert_or_assign(skill, level);
    };

private:
    size_t        id;
    std::string   name;
    std::string   title;
    inline static size_t next_id = 0;
    std::map<SkillType, size_t> skills;
};

#endif // !CREW_MEMBER_HPP
