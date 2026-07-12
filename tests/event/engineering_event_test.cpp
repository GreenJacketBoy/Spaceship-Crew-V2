#include <cstddef>
#include <gtest/gtest.h>
#include <memory>
#include "corridor.hpp"
#include "engineering_event.hpp"

TEST(EngineeringEvent, Init) {
    size_t crewMemberId = 0;
    EngineeringEvent medicalEvent = EngineeringEvent(0);
    EXPECT_DOUBLE_EQ(medicalEvent.getRoomId(), crewMemberId);
    EXPECT_EQ(medicalEvent.getType(), EventType::ENGINEERING);
    EXPECT_STREQ(medicalEvent.getTypeName(), "Engineering Event");
}

TEST(EngineeringEvent, Repair) {
    size_t roomId = 0;
    EngineeringEvent engineeringEvent = EngineeringEvent(0);
    CrewMember engineer = CrewMember("Karl", "Engineer", {});
    Room room = Room("Corridor", 1, 1, 1, std::make_unique<Corridor>(), {});
    
    bool didSucceed = engineeringEvent.repair(engineer, room);
    EXPECT_FALSE(didSucceed);

    engineer.setSkillLevel(SkillType::ENGINEERING, 100);
    didSucceed = engineeringEvent.repair(engineer, room);
    EXPECT_TRUE(didSucceed);
}