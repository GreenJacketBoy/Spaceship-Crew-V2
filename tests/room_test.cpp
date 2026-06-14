#include <cstddef>
#include <gtest/gtest.h>
#include "room.hpp"

TEST(RoomType, Name) {
  EXPECT_STREQ((Medbay()).getName().c_str(), "Medbay");
  EXPECT_STREQ((Corridor()).getName().c_str(), "Corridor");
  EXPECT_STREQ((Quarter()).getName().c_str(), "Quarter");
  EXPECT_STREQ((Bridge()).getName().c_str(), "Bridge");
}

TEST(RoomType, Type) {
  EXPECT_EQ((Medbay()).getType(), RoomTypeEnum::MEDBAY);
  EXPECT_EQ((Corridor()).getType(), RoomTypeEnum::CORRIDOR);
  EXPECT_EQ((Quarter()).getType(), RoomTypeEnum::QUARTER);
  EXPECT_EQ((Bridge()).getType(), RoomTypeEnum::BRIDGE);
}

TEST(Room, Create) {
  auto roomType = Medbay();
  size_t crewCapacity = 15, storageCapacity = 5, size = 30;
  auto room = Room("test room", crewCapacity, storageCapacity, size, &roomType);

  EXPECT_STREQ(room.getName().c_str(), "test room");
  EXPECT_EQ(room.getType(), roomType.getType());
  EXPECT_DOUBLE_EQ(room.getCrewCapacity(), crewCapacity);
  EXPECT_DOUBLE_EQ(room.getStorageCapacity(), storageCapacity);
  EXPECT_DOUBLE_EQ(room.getSize(), size);
  EXPECT_STREQ(room.getTypeName().c_str(), roomType.getName().c_str());
}
