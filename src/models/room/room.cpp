#include "room.hpp"
#include <iostream>

Room::Room(
    const std::string &name,
    size_t crewCapacity,
    size_t storageCapacity,
    size_t size,
    std::unique_ptr<RoomType> type,
    const std::vector<size_t> &adjacentRoomsIds
) {
    this->id = this->next_id;
    this->next_id++;
    
    this->name = name;
    this->type = std::move(type);
    this->size = size;
    this->storageCapacity = storageCapacity;
    this->crewCapacity = crewCapacity;
    this->adjacentRoomsIds = std::set<size_t>();
    for (auto roomId : adjacentRoomsIds) {
        this->adjacentRoomsIds.insert(roomId);
    }
    std::cout << "Room of name " << name << " and type " << this->getTypeName() << " has been created" << '\n';
};