#include "create_room_event.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include <cstddef>
#include <memory>
#include <qhashfunctions.h>
#include <sstream>
#include <vector>
#include "game_state.hpp"

void CreateRoomEvent::emitEvent(size_t &roomId) {
    for (auto subscriber : this->subscribers) {
        subscriber->handleRoomCreated(roomId);
    }
}

void CreateRoomEvent::createRoom(
    QString name,
    QString crewCapacity,
    QString storageCapacity,
    QString size,
    RoomTypeEnum type,
    QList<size_t> adjacentRoomsIds
) {
    auto &spaceShip = GameState::getInstance().getSpaceShip();
    if (!spaceShip) return;
    
    size_t crewCapacityNumber = -1;
    size_t storageCapacityNumber = -1;
    size_t sizeNumber = -1;
    auto stream = std::stringstream(crewCapacity.toStdString());
    stream >> crewCapacityNumber;
    stream.clear(); stream.str(storageCapacity.toStdString());
    stream >> storageCapacityNumber;
    stream.clear(); stream.str(size.toStdString());
    stream >> sizeNumber;

    std::vector<size_t> roomsAsVector;
    roomsAsVector.reserve(adjacentRoomsIds.size());
    for (size_t roomId : adjacentRoomsIds) {
        roomsAsVector.push_back(roomId);
    }

    auto room = std::unique_ptr<Room>(new Room(
        name.toStdString(),
        crewCapacityNumber,
        storageCapacityNumber,
        sizeNumber,
        type,
        roomsAsVector
    ));

    size_t roomId = room->getId();
    spaceShip->value().getRoomMap().insert({roomId, std::move(room)});

    this->emitEvent(roomId);
}
