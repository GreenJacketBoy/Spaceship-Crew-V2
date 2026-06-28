#ifndef QUARTER_HPP
#define QUARTER_HPP

#include "room_type.hpp"

class Quarter: public RoomType {
public: 
    Quarter() {
        this->type = RoomTypeEnum::QUARTER;
        this->name = "Quarter";
    }
    ~Quarter() override {}
};

#endif // !QUARTER_HPP