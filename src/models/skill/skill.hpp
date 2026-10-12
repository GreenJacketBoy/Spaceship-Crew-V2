#ifndef SKILL_HPP
#define SKILL_HPP

#include <cstddef>

enum class SkillType {
    MEDICAL,
    PILOTING,
    ENGINEERING,
};

// Not the end of the world if this is not updated, but it should be
const size_t AMOUNT_OF_SKILLS = static_cast<size_t>(SkillType::ENGINEERING) + 1;

struct Skill {
    SkillType type;
    size_t level;

    inline bool operator==(const Skill &skill) const {
        return type == skill.type && level == skill.level;
    }

    Skill(SkillType type, size_t level) noexcept {
        this->type = type;
        this->level = level;
    }
    

    Skill(const Skill &skill) noexcept {
        this->type = skill.type;
        this->level = skill.level;
    }
};

static const char* getSkillName(SkillType type) noexcept {
    switch (type) {
        case SkillType::MEDICAL:     return "Medical";
        case SkillType::PILOTING:    return "Piloting";
        case SkillType::ENGINEERING: return "Engineering";

        default: return "Unknwon Skill";
    }
}

#endif // !SKILL_HPP
