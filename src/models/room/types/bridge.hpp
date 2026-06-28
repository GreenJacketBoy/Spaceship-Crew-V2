#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "room_type.hpp"

class Bridge: public RoomType {
public: 
    Bridge() {
        this->type = RoomTypeEnum::BRIDGE;
        this->name = "Bridge";
    }
    ~Bridge() override {}
};

#endif // !BRIDGE_HPP
