#include "room.hpp"
#include "get_room.hpp"
#include <iostream>

Room::Room(
    std::string &&name,
    size_t crewCapacity,
    size_t storageCapacity,
    size_t size,
    RoomTypeEnum type,
    const std::vector<size_t> &adjacentRoomsIds
):
name(std::move(name)),
type(util::createRoomTypeFromEnum(type))
{
    this->id = this->next_id;
    this->next_id++;
    
    this->size = size;
    this->storageCapacity = storageCapacity;
    this->crewCapacity = crewCapacity;
    this->adjacentRoomsIds = std::set<size_t>();
    for (auto roomId : adjacentRoomsIds) {
        this->adjacentRoomsIds.insert(roomId);
    }
    std::cout << "Room of name " << this->name << " and type " << this->getTypeName() << " has been created" << '\n';
    if (adjacentRoomsIds.size() != 0) std::cout << "Adjacent Rooms:\n";
    for (auto adjacentRoomId : adjacentRoomsIds) {
        auto room = util::getRoom(adjacentRoomId);
        if (!room) continue;
        std::cout << "- #" << room.value()->getId() << " " << room.value()->getName() << '\n';
    }
};
