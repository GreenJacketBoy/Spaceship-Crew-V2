#include "space_ship.hpp"

SpaceShip::SpaceShip(
    std::string &&name,
    std::string &&flag,
    std::map<size_t, std::unique_ptr<CrewMember>> &&idToCrewMember_map,
    std::map<size_t, std::unique_ptr<Room>>       &&idToRoom_map 
): 
name(name), 
flag(flag),
idToRoom_map(std::move(idToRoom_map)),
idToCrewMember_map(std::move(idToCrewMember_map))
{
    this->id = this->next_id;
    this->next_id++;
}
