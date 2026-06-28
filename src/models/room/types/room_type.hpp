#ifndef ROOM_TYPE_H
#define ROOM_TYPE_H

enum class RoomTypeEnum {
    MEDBAY,
    CORRIDOR,
    QUARTER,
    BRIDGE,
};

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

#endif // !ROOM_TYPE_H
