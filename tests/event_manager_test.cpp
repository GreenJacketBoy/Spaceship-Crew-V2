#include <cstddef>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <qhashfunctions.h>
#include <qlist.h>
#include "create_crew_member_event.hpp"
#include "create_room_event.hpp"
#include "crew_member.hpp"
#include "game_state.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include "space_ship.hpp"

class TestRoomSubscriber : public CreateRoomSubscriber {
public:
    void handleRoomCreated(size_t &payload) override { this->receivedRoomId = payload; }
    auto &getReceivedRoomId() { return this->receivedRoomId; }
private:
    std::optional<size_t> receivedRoomId;
};

TEST(EventManager, CreateRoomEvent) {

    GameState &gameState = GameState::getInstance();
    TestRoomSubscriber testSubscriber;
    gameState.getEventManager().get()->getCreateRoomEvent().subscribe(testSubscriber);

    EXPECT_FALSE(testSubscriber.getReceivedRoomId().has_value());
    EXPECT_TRUE(gameState.getSpaceShip().get()->has_value());
    size_t amountOfRooms = gameState.getSpaceShip().get()->value().getRoomMap().size();

    gameState.getEventManager().get()->getCreateRoomEvent().createRoom(
        QString("Medbay Test"),
        "1",
        "18000",
        "50000000",
        RoomTypeEnum::MEDBAY,
        QList<size_t>({9, 10, 11})
    );

    EXPECT_TRUE(testSubscriber.getReceivedRoomId().has_value());
    EXPECT_DOUBLE_EQ(
        gameState.getSpaceShip().get()->value().getRoomMap().size(),
        amountOfRooms + 1
    );
    EXPECT_DOUBLE_EQ(
        gameState.getSpaceShip().get()->value().getRoomMap().at(testSubscriber.getReceivedRoomId().value())->getId(),
        testSubscriber.getReceivedRoomId().value()
    );

    Room *room = gameState.getSpaceShip().get()->value().getRoomMap().at(testSubscriber.getReceivedRoomId().value()).get();
    EXPECT_STREQ(room->getName().c_str(), "Medbay Test");
    EXPECT_DOUBLE_EQ(room->getCrewCapacity(), 1);
    EXPECT_DOUBLE_EQ(room->getStorageCapacity(), 18000);
    EXPECT_DOUBLE_EQ(room->getSize(), 50000000);
    EXPECT_EQ(room->getType(), RoomTypeEnum::MEDBAY);
    EXPECT_DOUBLE_EQ(room->getAdjacentRooms().size(), 3);
    EXPECT_TRUE(room->getAdjacentRooms().contains(9));
    EXPECT_TRUE(room->getAdjacentRooms().contains(10));
    EXPECT_TRUE(room->getAdjacentRooms().contains(11));
}

class TestCrewMemberSubscriber : public CreateCrewMemberSubscriber {
public:
    void handleCrewMemberCreated(size_t &payload) override { this->receivedCrewMemberId = payload; }
    auto &getReceivedCrewMemberId() { return this->receivedCrewMemberId; }
private:
    std::optional<size_t> receivedCrewMemberId;
};

TEST(EventManager, CreateCrewmemberEvent) {

    GameState &gameState = GameState::getInstance();
    TestCrewMemberSubscriber testSubscriber;
    gameState.getEventManager().get()->getCreateCrewMemberEvent().subscribe(testSubscriber);

    EXPECT_FALSE(testSubscriber.getReceivedCrewMemberId().has_value());
    EXPECT_TRUE(gameState.getSpaceShip().get()->has_value());
    size_t amountOfCrewMembers = gameState.getSpaceShip().get()->value().getCrewMap().size();

    gameState.getEventManager().get()->getCreateCrewMemberEvent().createCrewMember(
        QString("Johny Test"), // Lol
        "Lab rat",
        QList<size_t>()
    );

    EXPECT_TRUE(testSubscriber.getReceivedCrewMemberId().has_value());
    EXPECT_DOUBLE_EQ(
        gameState.getSpaceShip().get()->value().getCrewMap().size(),
        amountOfCrewMembers + 1
    );
    EXPECT_DOUBLE_EQ(
        gameState.getSpaceShip().get()->value().getCrewMap().at(testSubscriber.getReceivedCrewMemberId().value())->getId(),
        testSubscriber.getReceivedCrewMemberId().value()
    );

    CrewMember *crewMember = gameState.getSpaceShip().get()->value().getCrewMap().at(testSubscriber.getReceivedCrewMemberId().value()).get();
    EXPECT_STREQ(crewMember->getName().c_str(), "Johny Test");
    EXPECT_STREQ(crewMember->getTitle().c_str(), "Lab rat");
    EXPECT_DOUBLE_EQ(crewMember->getSkills().size(), 0); // TODO: handle Skills
}