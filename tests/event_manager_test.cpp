#include <cstddef>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <qhashfunctions.h>
#include <qlist.h>
#include <utility>
#include "create_crew_member_event.hpp"
#include "create_room_event.hpp"
#include "crew_member.hpp"
#include "game_state.hpp"
#include "get_crew_member.hpp"
#include "get_room.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include "skill.hpp"
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

    auto movedRoom1 = std::unique_ptr<Room>(new Room("Room 1", 1, 1, 1, RoomTypeEnum::CORRIDOR, {}));
    auto room1Id = movedRoom1->getId();
    auto movedRoom2 = std::unique_ptr<Room>(new Room("Room 2", 1, 1, 1, RoomTypeEnum::CORRIDOR, {}));
    auto room2Id = movedRoom2->getId();
    auto movedRoom3 = std::unique_ptr<Room>(new Room("Room 3", 1, 1, 1, RoomTypeEnum::CORRIDOR, {}));
    auto room3Id = movedRoom3->getId();

    gameState.getSpaceShip().get()->value().getRoomMap().insert({room1Id, std::move(movedRoom1)});
    gameState.getSpaceShip().get()->value().getRoomMap().insert({room2Id, std::move(movedRoom2)});
    gameState.getSpaceShip().get()->value().getRoomMap().insert({room3Id, std::move(movedRoom3)});

    EXPECT_DOUBLE_EQ(gameState.getSpaceShip().get()->value().getRoomMap().at(room1Id)->getId(), room1Id);
    EXPECT_DOUBLE_EQ(gameState.getSpaceShip().get()->value().getRoomMap().at(room2Id)->getId(), room2Id);
    EXPECT_DOUBLE_EQ(gameState.getSpaceShip().get()->value().getRoomMap().at(room3Id)->getId(), room3Id);
    
    size_t amountOfRooms = gameState.getSpaceShip().get()->value().getRoomMap().size();

    auto list = QList<size_t>({ room1Id, room2Id });
    gameState.getEventManager().get()->getCreateRoomEvent().createRoom(
        QString("Medbay Test"),
        "1",
        "18000",
        "50000000",
        RoomTypeEnum::MEDBAY,
        &list
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
    EXPECT_DOUBLE_EQ(room->getAdjacentRooms().size(), 2);
    EXPECT_TRUE(room->getAdjacentRooms().contains(room1Id));
    EXPECT_TRUE(gameState.getSpaceShip().get()->value().getRoomMap().at(room1Id).get()->getAdjacentRooms().contains(room->getId()));
    EXPECT_TRUE(room->getAdjacentRooms().contains(room2Id));
    EXPECT_TRUE(gameState.getSpaceShip().get()->value().getRoomMap().at(room2Id).get()->getAdjacentRooms().contains(room->getId()));
    EXPECT_FALSE(room->getAdjacentRooms().contains(room3Id));
    EXPECT_FALSE(gameState.getSpaceShip().get()->value().getRoomMap().at(room3Id).get()->getAdjacentRooms().contains(room->getId()));
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

    auto list = QList<Skill>({
        {SkillType::ENGINEERING, 1},
        {SkillType::PILOTING, 10},
    });
    gameState.getEventManager().get()->getCreateCrewMemberEvent().createCrewMember(
        QString("Johny Test"), // Lol
        "Lab rat",
        std::nullopt, // TODO: test current Room
        &list // TODO: test skills
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
    EXPECT_DOUBLE_EQ(crewMember->getSkills().size(), 2);
    EXPECT_DOUBLE_EQ(crewMember->getSkills().at(SkillType::ENGINEERING), 1);
    EXPECT_DOUBLE_EQ(crewMember->getSkills().at(SkillType::PILOTING), 10);
}

TEST(EventManager, CrewMemberMovedEvent) {

    GameState &gameState = GameState::getInstance();
    auto &spaceShip = gameState.getSpaceShip().get()->value();
    
    auto movedCrewMember = std::unique_ptr<CrewMember>(new CrewMember("James", "Pilot", {}));
    size_t crewMemberId = movedCrewMember->getId();
    auto movedRoom1 = std::unique_ptr<Room>(new Room("Room 1", 1, 1, 1, RoomTypeEnum::CORRIDOR, {}));
    size_t room1Id = movedRoom1->getId();
    auto movedRoom2 = std::unique_ptr<Room>(new Room("Room 2", 1, 1, 1, RoomTypeEnum::CORRIDOR, {}));
    size_t room2Id = movedRoom2->getId();

    spaceShip.getRoomMap().insert({movedRoom1->getId(), std::move(movedRoom1)});
    spaceShip.getRoomMap().insert({movedRoom2->getId(), std::move(movedRoom2)});
    spaceShip.getCrewMap().insert({movedCrewMember->getId(), std::move(movedCrewMember)});

    auto crewMember = util::getCrewMember(crewMemberId).value();
    auto room1 = util::getRoom(room1Id).value();
    auto room2 = util::getRoom(room2Id).value();

    EXPECT_FALSE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 0);
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 0);

    CrewMemberMovedPayload payload = {
        crewMember->getId(),
        std::nullopt,
        std::nullopt,
    };
    // Nothing happens
    gameState.getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    EXPECT_FALSE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 0);
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 0);

    payload = {
        crewMember->getId(),
        room1->getId(),
        std::nullopt,
    };
    // Nothing happens
    gameState.getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    EXPECT_FALSE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 0);
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 0);

    payload = {
        crewMember->getId(),
        std::nullopt,
        room1->getId(),
    };
    // CrewMember is in Room1
    gameState.getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    EXPECT_TRUE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(crewMember->getAssociatedRooms().getCurrentRoom().value(),  room1->getId());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 1);
    EXPECT_TRUE(room1->getCrewMembersInRoom().contains(crewMember->getId()));
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 0);

    payload = {
        crewMember->getId(),
        room1->getId(),
        room2->getId(),
    };
    // CrewMember is in Room2 and was in Room1
    gameState.getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    EXPECT_TRUE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(crewMember->getAssociatedRooms().getCurrentRoom().value(),  room2->getId());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 0);
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 1);
    EXPECT_TRUE(room2->getCrewMembersInRoom().contains(crewMember->getId()));

    payload = {
        crewMember->getId(),
        std::nullopt,
        room1->getId(),
    };
    // CrewMember is in Room1 but it's not specified it was in Room2 before (should not happen, but good to know it can)
    gameState.getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    EXPECT_TRUE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(crewMember->getAssociatedRooms().getCurrentRoom().value(),  room1->getId());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 1);
    EXPECT_TRUE(room1->getCrewMembersInRoom().contains(crewMember->getId()));
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 1);
    EXPECT_TRUE(room2->getCrewMembersInRoom().contains(crewMember->getId()));


    payload = {
        crewMember->getId(),
        room1->getId(),
        std::nullopt,
    };
    // CrewMember back to no Room from being in Room1
    gameState.getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    EXPECT_FALSE(crewMember->getAssociatedRooms().getCurrentRoom().has_value());
    EXPECT_DOUBLE_EQ(room1->getCrewMembersInRoom().size(), 0);
    // still in from the test before, this is normal
    EXPECT_DOUBLE_EQ(room2->getCrewMembersInRoom().size(), 1);
    EXPECT_TRUE(room2->getCrewMembersInRoom().contains(crewMember->getId()));
}
