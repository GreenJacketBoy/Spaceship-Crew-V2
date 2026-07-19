#ifndef SPACE_SHIP_HPP
#define SPACE_SHIP_HPP

#include "crew_member.hpp"
#include "room.hpp"
#include <cstddef>
#include <map>
#include <memory>
#include <string>

class SpaceShip {
public: 
    SpaceShip(
        std::string &&name,
        std::string &&flag,
        std::map<size_t, std::unique_ptr<CrewMember>> &&idToCrewMember_map,
        std::map<size_t, std::unique_ptr<Room>>       &&idToRoom_map 
    );

    inline size_t             getId()      { return this->id;   }
    inline const std::string &getName()    { return this->name; }
    inline const std::string &getFlag()    { return this->flag; }
    inline auto              &getCrewMap() { return this->idToCrewMember_map; }
    inline auto              &getRoomMap() { return this->idToRoom_map;       }

    inline void setName(std::string &&name) { this->name  = name; }
    inline void setFlag(std::string &&flag) { this->flag = flag;  }

private:
    size_t       id;
    std::string  name;
    std::string  flag;
    std::map<size_t, std::unique_ptr<CrewMember>> idToCrewMember_map;
    std::map<size_t, std::unique_ptr<Room>>       idToRoom_map;
    inline static size_t next_id = 0;
};

#endif // !SPACE_SHIP_HPP
