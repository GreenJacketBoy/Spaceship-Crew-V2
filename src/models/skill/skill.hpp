#ifndef SKILL_HPP
#define SKILL_HPP

#include <cstddef>

enum class SkillType {
    MEDICAL,
    PILOTING,
    ENGINEERING,
};

struct Skill {
    SkillType type;
    size_t level;
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
