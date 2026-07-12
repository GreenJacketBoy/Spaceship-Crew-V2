#include <cstddef>
#include <gtest/gtest.h>
#include "crew_member.hpp"
#include "event.hpp"
#include "medical_event.hpp"
#include "skill.hpp"

TEST(MedicalEvent, Init) {
    size_t crewMemberId = 0;
    MedicalEvent medicalEvent = MedicalEvent(0);
    EXPECT_DOUBLE_EQ(medicalEvent.getCrewMemberId(), crewMemberId);
    EXPECT_EQ(medicalEvent.getType(), EventType::MEDICAL);
    EXPECT_STREQ(medicalEvent.getTypeName(), "Medical Event");
}

TEST(MedicalEvent, Heal) {
    size_t crewMemberId = 0;
    MedicalEvent medicalEvent = MedicalEvent(0);
    CrewMember healer = CrewMember("James", "Pilot", {});
    CrewMember patient = CrewMember("Karl", "Engineer about to die", {});
    
    bool didSucceed = medicalEvent.heal(healer, patient);
    EXPECT_FALSE(didSucceed);

    healer.setSkillLevel(SkillType::MEDICAL, 100);
    didSucceed = medicalEvent.heal(healer, patient);
    EXPECT_TRUE(didSucceed);
}
