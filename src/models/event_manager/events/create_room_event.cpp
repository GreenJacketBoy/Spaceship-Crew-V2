#include "create_room_event.hpp"
#include "get_room.hpp"
#include "get_room_list.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include <cstddef>
#include <memory>
#include <qhashfunctions.h>
#include <sstream>
#include <vector>

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
    QList<size_t> *adjacentRoomsIds
) {
    auto optionalRoomMap = util::getRoomList();
    if (!optionalRoomMap) return;
    auto roomMap = optionalRoomMap.value();
    
    size_t crewCapacityNumber = -1;
    size_t storageCapacityNumber = -1;
    size_t sizeNumber = -1;
    auto stream = std::stringstream(crewCapacity.toStdString());
    stream >> crewCapacityNumber;
    stream.clear(); stream.str(storageCapacity.toStdString());
    stream >> storageCapacityNumber;
    stream.clear(); stream.str(size.toStdString());
    stream >> sizeNumber;

    std::vector<size_t> roomIdsAsVector;
    roomIdsAsVector.reserve(adjacentRoomsIds->size());
    std::vector<Room *> roomPointers;
    roomPointers.reserve(adjacentRoomsIds->size());

    for (size_t roomId : *adjacentRoomsIds) {
        auto optionalRoom = util::getRoom(roomId);
        if (!optionalRoom) continue;
        roomPointers.push_back(optionalRoom.value());
        roomIdsAsVector.push_back(roomId);
    }

    auto room = std::unique_ptr<Room>(new Room(
        name.toStdString(),
        crewCapacityNumber,
        storageCapacityNumber,
        sizeNumber,
        type,
        roomIdsAsVector
    ));

    size_t roomId = room->getId();
    roomMap->insert({roomId, std::move(room)});

    for (auto adjacentRoom : roomPointers) {
        adjacentRoom->getAdjacentRooms().insert(roomId);
    }

    this->emitEvent(roomId);
}
