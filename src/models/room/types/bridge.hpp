#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "room_type.hpp"

class Bridge: public RoomType {
public: 
    ~Bridge() override {}
    inline std::string  getName() override { return "Bridge"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::BRIDGE; }
};

#endif // !BRIDGE_HPP
