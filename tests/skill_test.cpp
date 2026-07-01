#include <gtest/gtest.h>
#include "skill.hpp"

TEST(Skill, GetName) {
  EXPECT_STREQ(getSkillName(SkillType::ENGINEERING), "Engineering");
  EXPECT_STREQ(getSkillName(SkillType::MEDICAL), "Medical");
  EXPECT_STREQ(getSkillName(SkillType::PILOTING), "Piloting");
  EXPECT_STREQ(getSkillName((SkillType) -1), "Unknwon Skill");
}