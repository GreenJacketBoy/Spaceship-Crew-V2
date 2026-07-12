#include <cstddef>
#include <gtest/gtest.h>
#include "room.hpp"
#include "medbay.hpp"
#include "corridor.hpp"
#include "quarter.hpp"
#include "bridge.hpp"

TEST(RoomType, Name) {
  EXPECT_STREQ((Medbay()).getName(), "Medbay");
  EXPECT_STREQ((Corridor()).getName(), "Corridor");
  EXPECT_STREQ((Quarter()).getName(), "Quarter");
  EXPECT_STREQ((Bridge()).getName(), "Bridge");
}

TEST(RoomType, Type) {
  EXPECT_EQ((Medbay()).getType(), RoomTypeEnum::MEDBAY);
  EXPECT_EQ((Corridor()).getType(), RoomTypeEnum::CORRIDOR);
  EXPECT_EQ((Quarter()).getType(), RoomTypeEnum::QUARTER);
  EXPECT_EQ((Bridge()).getType(), RoomTypeEnum::BRIDGE);
}

TEST(Room, Create) {
  size_t crewCapacity = 15, storageCapacity = 5, size = 30;
  std::vector<size_t> adjacentRooms;
  Room room = Room("test room", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);

  EXPECT_STREQ(room.getName().c_str(), "test room");
  EXPECT_EQ(room.getType(), Medbay().getType());
  EXPECT_DOUBLE_EQ(room.getCrewCapacity(), crewCapacity);
  EXPECT_DOUBLE_EQ(room.getStorageCapacity(), storageCapacity);
  EXPECT_DOUBLE_EQ(room.getSize(), size);
  EXPECT_STREQ(room.getTypeName(), Medbay().getName());
}

TEST(Room, InitAdjacentRooms) {
  size_t crewCapacity = 15, storageCapacity = 5, size = 30;

  std::array<Room, 3> rooms = {
    Room("test room 1", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
    Room("test room 2", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
    Room("test room 3", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
  };

  std::vector<size_t> adjacentRooms;
  Room room = Room("test room 4", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 0);

  adjacentRooms = { rooms.at(0).getId() };
  room = Room("test room 5", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 1);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(0).getId()));

  adjacentRooms = { 
    rooms.at(0).getId(),
    rooms.at(1).getId()
  };
  room = Room("test room 6", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 2);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(0).getId()));
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(1).getId()));

  adjacentRooms = { 
    rooms.at(0).getId(),
    rooms.at(1).getId(),
    rooms.at(2).getId()
  };
  room = Room("test room 7", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 3);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(0).getId()));
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(1).getId()));
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(2).getId()));
}

TEST(Room, AddAdjacentRoom) {
  size_t crewCapacity = 15, storageCapacity = 5, size = 30;

  std::array<Room, 3> rooms = {
    Room("test room 1", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
    Room("test room 2", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
    Room("test room 3", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
  };
  
  std::vector<size_t> adjacentRooms = { };
  Room room = Room("test room 4", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 0);

  room.addAdjacentRoom(rooms.at(0).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 1);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(0).getId()));

  room.addAdjacentRoom(rooms.at(1).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 2);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(1).getId()));

  room.addAdjacentRoom(rooms.at(2).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 3);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(2).getId()));

  // same with already initialized adjacent rooms :
  adjacentRooms = { rooms.at(0).getId() };
  room = Room("test room 5", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 1);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(0).getId()));

  room.addAdjacentRoom(rooms.at(1).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 2);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(1).getId()));

  room.addAdjacentRoom(rooms.at(2).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 3);
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(2).getId()));
}

TEST(Room, RemoveAdjacentRoom) {
  size_t crewCapacity = 15, storageCapacity = 5, size = 30;

  std::array<Room, 3> rooms = {
    Room("test room 1", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
    Room("test room 2", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
    Room("test room 3", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), std::vector<size_t>()),
  };
  
  std::vector<size_t> adjacentRooms = { 
    rooms.at(0).getId(),
    rooms.at(1).getId(),
    rooms.at(2).getId(),
   };
  Room room = Room("test room 4", crewCapacity, storageCapacity, size, std::make_unique<Medbay>(), adjacentRooms);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 3);

  room.removeAdjacentRoom(rooms.at(0).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 2);
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(0).getId()));
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(1).getId()));
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(2).getId()));

  room.removeAdjacentRoom(rooms.at(1).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 1);
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(0).getId()));
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(1).getId()));
  EXPECT_TRUE(room.isRoomAdjacent(rooms.at(2).getId()));

  room.removeAdjacentRoom(rooms.at(2).getId());
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 0);
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(0).getId()));
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(1).getId()));
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(2).getId()));

  room.removeAdjacentRoom(9999999);
  EXPECT_DOUBLE_EQ(room.getAdjacentRooms().size(), 0);
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(0).getId()));
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(1).getId()));
  EXPECT_FALSE(room.isRoomAdjacent(rooms.at(2).getId()));
}
