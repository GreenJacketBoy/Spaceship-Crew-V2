#ifndef QUARTER_HPP
#define QUARTER_HPP

#include "room_type.hpp"

class Quarter: public RoomType {
public: 
    ~Quarter() override {}
    inline std::string  getName() override { return "Quarter"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::QUARTER; }
};

#endif // !QUARTER_HPP