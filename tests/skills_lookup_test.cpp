#include <array>
#include <gtest/gtest.h>
#include <optional>
#include <qlist.h>
#include "game_state.hpp"
#include "skill.hpp"
#include "skills_lookup.hpp"

TEST(SkillsLookup, eventHandlersEffectsOnTheSkillMaps) {
  auto &gameState = GameState::getInstance();
  auto eventManager = gameState.getEventManager().get();
  gameState.triggerSubscriptions();

  std::array<SkillType, 3> skillTypes = {
    SkillType::ENGINEERING,
    SkillType::MEDICAL,
    SkillType::PILOTING,
  };
  EXPECT_DOUBLE_EQ(AMOUNT_OF_SKILLS, skillTypes.size());
  auto skillsLookup = GameState::getInstance().getSkillsLookup().get();

  for (SkillType skillType : skillTypes) {
    EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  QList<Skill> emptySkillsList;
  auto crewMemberJamesId = eventManager->getCreateCrewMemberEvent().createCrewMember("James", "Pilot", std::nullopt, &emptySkillsList);
  // create crew member james with no skill at all
  EXPECT_TRUE(crewMemberJamesId);

  for (SkillType skillType : skillTypes) {
    EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  QList<Skill> karlSkillsList = { { SkillType::ENGINEERING, 6 }, { SkillType::PILOTING, 0 } };
  // create crew member karl with Engineering skill at level 6, and Piloting skill at 0 that should be counted as not having the skill
  auto crewMemberKarlId = eventManager->getCreateCrewMemberEvent().createCrewMember("Karl", "Engineer", std::nullopt, &karlSkillsList);
  EXPECT_TRUE(crewMemberKarlId);

  for (SkillType skillType : skillTypes) {
    if (skillType == SkillType::ENGINEERING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(6));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(6).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(6).contains(crewMemberKarlId.value()));
    }
    else EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  CrewMemberSkillUpdatedPayload skillUpdatedPayload_1 = {
    crewMemberKarlId.value(),
    SkillType::ENGINEERING,
    0,
    6
  };
  // remove Engineering skill from karl
  eventManager->getCrewMemberSkillUpdatedEvent().emitEvent(skillUpdatedPayload_1);
  
  for (SkillType skillType : skillTypes) {
    EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  CrewMemberSkillUpdatedPayload skillUpdatedPayload_2 = {
    crewMemberJamesId.value(),
    SkillType::PILOTING,
    7,
    0
  };
  // add Piloting skill to james
  eventManager->getCrewMemberSkillUpdatedEvent().emitEvent(skillUpdatedPayload_2);

  for (SkillType skillType : skillTypes) {
    if (skillType == SkillType::PILOTING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(7));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(7).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberJamesId.value()));
    }
    else EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  CrewMemberSkillUpdatedPayload skillUpdatedPayload_3 = {
    crewMemberKarlId.value(),
    SkillType::PILOTING,
    1,
    0
  };
  // add Piloting skill level 1 (different from james, which has 7) to karl
  eventManager->getCrewMemberSkillUpdatedEvent().emitEvent(skillUpdatedPayload_3);

  for (SkillType skillType : skillTypes) {
    if (skillType == SkillType::PILOTING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 2);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(7));
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(1));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(7).size(), 1);
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(1).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberJamesId.value()));
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(1).contains(crewMemberKarlId.value()));
    }
    else EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  CrewMemberSkillUpdatedPayload skillUpdatedPayload_4 = {
    crewMemberKarlId.value(),
    SkillType::PILOTING,
    7,
    1
  };
  // set Piloting skill level 7 (same as james) to karl
  eventManager->getCrewMemberSkillUpdatedEvent().emitEvent(skillUpdatedPayload_4);

  for (SkillType skillType : skillTypes) {
    if (skillType == SkillType::PILOTING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(7));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(7).size(), 2);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberJamesId.value()));
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberKarlId.value()));
    }
    else EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  CrewMemberSkillUpdatedPayload skillUpdatedPayload_5 = {
    crewMemberKarlId.value(),
    SkillType::ENGINEERING,
    6,
    0
  };
  // add Engineering skill to karl
  eventManager->getCrewMemberSkillUpdatedEvent().emitEvent(skillUpdatedPayload_5);

  for (SkillType skillType : skillTypes) {
    if (skillType == SkillType::PILOTING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(7));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(7).size(), 2);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberJamesId.value()));
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberKarlId.value()));
    }
    else if (skillType == SkillType::ENGINEERING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(6));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(6).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(6).contains(crewMemberKarlId.value()));
    }
    else EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  // delete crew member karl
  eventManager->getCrewMemberDeletedEvent().deleteCrewMember(crewMemberKarlId.value());

  for (SkillType skillType : skillTypes) {
    if (skillType == SkillType::PILOTING) {
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).contains(7));
      EXPECT_DOUBLE_EQ(skillsLookup->getConstSkillMap(skillType).at(7).size(), 1);
      EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).at(7).contains(crewMemberJamesId.value()));
    }
    else EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }

  // delete crew member james
  eventManager->getCrewMemberDeletedEvent().deleteCrewMember(crewMemberJamesId.value());

  for (SkillType skillType : skillTypes) {
    EXPECT_TRUE(skillsLookup->getConstSkillMap(skillType).empty());
  }
}
