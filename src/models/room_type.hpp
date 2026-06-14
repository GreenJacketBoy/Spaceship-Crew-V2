#include <string>

enum class RoomTypeEnum {
    MEDBAY,
    CORRIDOR,
    QUARTER,
    BRIDGE,
};

class RoomType {
public: 
    virtual inline std::string getName() = 0;
    virtual inline RoomTypeEnum getType() = 0;
};

/* 
 * Implementations
 */

class Medbay: public RoomType {
public: 
    std::string  getName() override { return "Medbay"; }
    RoomTypeEnum getType() override { return RoomTypeEnum::MEDBAY; }
};

class Corridor: public RoomType {
public: 
    std::string  getName() override { return "Corridor"; }
    RoomTypeEnum getType() override { return RoomTypeEnum::CORRIDOR; }
};

class Quarter: public RoomType {
public: 
    std::string  getName() override { return "Quarter"; }
    RoomTypeEnum getType() override { return RoomTypeEnum::QUARTER; }
};

class Bridge: public RoomType {
public: 
    std::string  getName() override { return "Bridge"; }
    RoomTypeEnum getType() override { return RoomTypeEnum::BRIDGE; }
};
