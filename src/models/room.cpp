#include "room.hpp"
#include <iostream>

Room::Room(
    const std::string &name,
    size_t crewCapacity,
    size_t storageCapacity,
    size_t size,
    RoomType *type
) {
    this->name = name;
    this->type = type;
    this->size = size;
    this->storageCapacity = storageCapacity;
    this->crewCapacity = crewCapacity;
    std::cout << "Room of name " << name << " and type " << type->getName() << " has been created" << '\n';
}
