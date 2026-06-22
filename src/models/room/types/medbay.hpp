#ifndef MEDBAY_HPP
#define MEDBAY_HPP
#include "room_type.hpp"


class Medbay: public RoomType {
public: 
    ~Medbay() override {}
    inline std::string  getName() override { return "Medbay"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::MEDBAY; }
};

#endif // !MEDBAY_HPP
