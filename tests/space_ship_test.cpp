#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "corridor.hpp"
#include "crew_member.hpp"
#include "room.hpp"
#include "space_ship.hpp"

TEST(SpaceShip, Init) {

  auto crewMap = std::map<size_t, std::unique_ptr<CrewMember>>();
  auto roomMap = std::map<size_t, std::unique_ptr<Room>>();
  SpaceShip spaceShip = SpaceShip("Antarctica", "HCS", std::move(crewMap), std::move(roomMap));

  EXPECT_STREQ(spaceShip.getName().c_str(), "Antarctica");
  EXPECT_STREQ(spaceShip.getFlag().c_str(), "HCS");
  EXPECT_NO_THROW(spaceShip.getId());
}

TEST(SpaceShip, InitWithRooms) {
  std::map<size_t, std::unique_ptr<Room>> roomMap;
  roomMap.insert({1, std::unique_ptr<Room>(new Room("Room 1", 1, 1, 1, std::make_unique<Corridor>(), {}))});
  roomMap.insert({2, std::unique_ptr<Room>(new Room("Room 2", 1, 1, 1, std::make_unique<Corridor>(), {}))});
  roomMap.insert({3, std::unique_ptr<Room>(new Room("Room 3", 1, 1, 1, std::make_unique<Corridor>(), {}))});

  SpaceShip spaceShip = SpaceShip("Antarctica", "HCS", {}, std::move(roomMap));

  EXPECT_STREQ(spaceShip.getRoomMap().at(1)->getName().c_str(), "Room 1");
  EXPECT_STREQ(spaceShip.getRoomMap().at(2)->getName().c_str(), "Room 2");
  EXPECT_STREQ(spaceShip.getRoomMap().at(3)->getName().c_str(), "Room 3");
  EXPECT_THROW(spaceShip.getRoomMap().at(4), std::out_of_range);
}

TEST(SpaceShip, InitWithCrew) {
  std::map<size_t, std::unique_ptr<CrewMember>> crewMap;
  crewMap.insert({1, std::unique_ptr<CrewMember>(new CrewMember("James", "Pilot", {}))});
  crewMap.insert({2, std::unique_ptr<CrewMember>(new CrewMember("Amanda", "Computer expert", {}))});
  crewMap.insert({3, std::unique_ptr<CrewMember>(new CrewMember("Karl", "Engineer", {}))});

  SpaceShip spaceShip = SpaceShip("Antarctica", "HCS", std::move(crewMap), {});

  EXPECT_STREQ(spaceShip.getCrewMap().at(1)->getName().c_str(), "James");
  EXPECT_STREQ(spaceShip.getCrewMap().at(2)->getName().c_str(), "Amanda");
  EXPECT_STREQ(spaceShip.getCrewMap().at(3)->getName().c_str(), "Karl");
  EXPECT_THROW(spaceShip.getCrewMap().at(4), std::out_of_range);
}