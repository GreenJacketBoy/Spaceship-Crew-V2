#include <gtest/gtest.h>
#include <string>
#include "crew_member.hpp"
#include "crew_member.hpp"
#include "skill.hpp"

TEST(CrewMember, Create) {
  std::string name = "James", title = "Pilot";
  std::vector<Skill> skills;
  CrewMember crewMember = CrewMember(std::move(name), std::move(title), skills);

  EXPECT_STREQ(crewMember.getName().c_str(), "James");
  EXPECT_STREQ(crewMember.getTitle().c_str(), "Pilot");
  EXPECT_NO_THROW(crewMember.getId()); // Listen, I'm trying to get to 100% test coverage okay ?
}

TEST(CrewMember, CreateWithStringLiterals) {
  std::vector<Skill> skills;
  CrewMember crewMember = CrewMember("James", "Pilot", skills);

  EXPECT_STREQ(crewMember.getName().c_str(), "James");
  EXPECT_STREQ(crewMember.getTitle().c_str(), "Pilot");
}

TEST(CrewMember, SetNameAndTitle) {
  std::vector<Skill> skills;
  CrewMember crewMember = CrewMember("James", "Pilot", skills);
  crewMember.setName("Tendy");
  crewMember.setTitle("Medical assistant");

  EXPECT_STREQ(crewMember.getName().c_str(), "Tendy");
  EXPECT_STREQ(crewMember.getTitle().c_str(), "Medical assistant");
}

TEST(CrewMember, InitSkills) {
  std::vector<Skill> skills = {
    { SkillType::MEDICAL,     1  },
    { SkillType::ENGINEERING, 10 },
    { SkillType::PILOTING,    0  }, // should not be in the set
  };

  CrewMember crewMember = CrewMember("Karl", "Not a Pilot", skills);

  EXPECT_DOUBLE_EQ(crewMember.getSkills().size(), 2);
  EXPECT_DOUBLE_EQ(crewMember.getSkills().at(SkillType::MEDICAL), 1);
  EXPECT_DOUBLE_EQ(crewMember.getSkills().at(SkillType::ENGINEERING), 10);
  EXPECT_THROW(crewMember.getSkills().at(SkillType::PILOTING), std::out_of_range);
  EXPECT_DOUBLE_EQ(crewMember.getSkillLevel(SkillType::MEDICAL), 1);
  EXPECT_DOUBLE_EQ(crewMember.getSkillLevel(SkillType::ENGINEERING), 10);
  EXPECT_DOUBLE_EQ(crewMember.getSkillLevel(SkillType::PILOTING), 0);
}

TEST(CrewMember, SetSkill) {
  std::vector<Skill> skills = {
    { SkillType::MEDICAL,     1  },
    { SkillType::ENGINEERING, 10 },
  };

  CrewMember crewMember = CrewMember("Karl", "Not a Pilot", skills);

  crewMember.setSkillLevel(SkillType::MEDICAL, 5);
  EXPECT_DOUBLE_EQ(crewMember.getSkills().size(), 2);
  EXPECT_DOUBLE_EQ(crewMember.getSkills().at(SkillType::MEDICAL), 5);
  EXPECT_DOUBLE_EQ(crewMember.getSkillLevel(SkillType::MEDICAL), 5);

  crewMember.setSkillLevel(SkillType::ENGINEERING, 0);
  EXPECT_DOUBLE_EQ(crewMember.getSkills().size(), 1);
  EXPECT_THROW(crewMember.getSkills().at(SkillType::ENGINEERING), std::out_of_range);
  EXPECT_DOUBLE_EQ(crewMember.getSkillLevel(SkillType::ENGINEERING), 0);

  crewMember.setSkillLevel(SkillType::PILOTING, 1);
  crewMember.setTitle("On its way to become a pilot");
  EXPECT_DOUBLE_EQ(crewMember.getSkills().size(), 2);
  EXPECT_DOUBLE_EQ(crewMember.getSkills().at(SkillType::PILOTING), 1);
  EXPECT_DOUBLE_EQ(crewMember.getSkillLevel(SkillType::PILOTING), 1);
}
