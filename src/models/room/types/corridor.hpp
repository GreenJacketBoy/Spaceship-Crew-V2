#ifndef CORRIDOR_HPP
#define CORRIDOR_HPP

#include "room_type.hpp"

class Corridor: public RoomType {
public: 
    ~Corridor() override {}
    inline std::string  getName() override { return "Corridor"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::CORRIDOR; }
};

#endif // !CORRIDOR_HPP
