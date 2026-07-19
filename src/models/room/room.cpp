#include "room.hpp"
#include <iostream>

Room::Room(
    std::string &&name,
    size_t crewCapacity,
    size_t storageCapacity,
    size_t size,
    std::unique_ptr<RoomType> &&type,
    const std::vector<size_t> &adjacentRoomsIds
):
name(std::move(name)),
type(std::move(type))
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
    std::cout << "Room of name " << name << " and type " << this->getTypeName() << " has been created" << '\n';
};
