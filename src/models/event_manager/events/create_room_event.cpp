#include "create_room_event.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include <cstddef>
#include <memory>
#include <vector>
#include "game_state.hpp"

void CreateRoomEvent::emitEvent(size_t &roomId) {
    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomCreated(roomId);
    }
}

void CreateRoomEvent::createRoom(
    QString name,
    size_t crewCapacity,
    size_t storageCapacity,
    size_t size,
    RoomTypeEnum type,
    QList<size_t> adjacentRoomsIds
) {
    auto &spaceShip = GameState::getInstance().getSpaceShip();
    if (!spaceShip) return;

    std::vector<size_t> roomsAsVector;
    roomsAsVector.reserve(adjacentRoomsIds.size());
    for (size_t roomId : adjacentRoomsIds) {
        roomsAsVector.push_back(roomId);
    }

    auto room = std::unique_ptr<Room>(new Room(
        name.toStdString(),
        crewCapacity,
        storageCapacity,
        size,
        type,
        roomsAsVector
    ));

    size_t roomId = room->getId();
    spaceShip->value().getRoomMap().insert({roomId, std::move(room)});

    this->emitEvent(roomId);
}
