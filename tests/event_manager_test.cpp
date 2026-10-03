#include <cstddef>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <qhashfunctions.h>
#include <qlist.h>
#include "create_room_event.hpp"
#include "game_state.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include "space_ship.hpp"

class TestSubscriber : public CreateRoomSubscriber {
public:
    void handleRoomCreated(size_t &payload) { this->receivedRoomId = payload; }
    auto &getReceivedRoomId() { return this->receivedRoomId; }
private:
    std::optional<size_t> receivedRoomId;
};

TEST(EventManager, CreateRoomEvent) {

    GameState &gameState = GameState::getInstance();
    TestSubscriber testSubscriber;
    gameState.getEventManager().get()->getCreateRoomEvent().subscribe(testSubscriber);

    EXPECT_FALSE(testSubscriber.getReceivedRoomId().has_value());
    EXPECT_TRUE(gameState.getSpaceShip().get()->has_value());
    size_t amountOfRooms = gameState.getSpaceShip().get()->value().getRoomMap().size();

    gameState.getEventManager().get()->getCreateRoomEvent().createRoom(
        QString("Medbay Test"),
        1,
        1,
        1,
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
}