#ifndef CORRIDOR_HPP
#define CORRIDOR_HPP

#include "room_type.hpp"

class Corridor: public RoomType {
public: 
    Corridor() {
        this->type = RoomTypeEnum::CORRIDOR;
        this->name = "Corridor";
    }
    ~Corridor() override {}
};

#endif // !CORRIDOR_HPP
