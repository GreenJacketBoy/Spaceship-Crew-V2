#ifndef MEDBAY_HPP
#define MEDBAY_HPP
#include "room_type.hpp"


class Medbay: public RoomType {
public: 
    Medbay() {
        this->type = RoomTypeEnum::MEDBAY;
        this->name = "Medbay";
    }
    ~Medbay() override {}
};

#endif // !MEDBAY_HPP
