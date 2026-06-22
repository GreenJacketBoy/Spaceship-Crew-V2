#ifndef ROOM_TYPE_H
#define ROOM_TYPE_H

#include <string>

enum class RoomTypeEnum {
    MEDBAY,
    CORRIDOR,
    QUARTER,
    BRIDGE,
};

class RoomType {
public:
    virtual ~RoomType() {};
    virtual std::string getName() = 0; 
    virtual RoomTypeEnum getType() = 0; 
};

#endif // !ROOM_TYPE_H
