#ifndef ROOM_TYPE_H
#define ROOM_TYPE_H

#include <cstddef>
enum class RoomTypeEnum {
    MEDBAY,
    CORRIDOR,
    QUARTER,
    BRIDGE,
};

// Not the end of the world if this is not updated, but it should be
const size_t AMOUNT_OF_ROOM_TYPES = static_cast<size_t>(RoomTypeEnum::BRIDGE) + 1;

class RoomType {
public:
    virtual ~RoomType() {};
    virtual const char* getName() final { return this->name; }
    virtual RoomTypeEnum getType() final { return this->type; }

protected:
    RoomTypeEnum type;
    // String literal instead of std::string because they are stored in .rodata, not the stack or the heap
    // https://en.cppreference.com/cpp/language/string_literal
    const char* name;
};

namespace util {
    RoomType createRoomTypeFromEnum(RoomTypeEnum type);
}

#endif // !ROOM_TYPE_H
