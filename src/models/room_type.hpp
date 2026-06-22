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

/* 
 * Implementations
 */

class Medbay: public RoomType {
public: 
    ~Medbay() override {}
    inline std::string  getName() override { return "Medbay"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::MEDBAY; }
};

class Corridor: public RoomType {
public: 
    ~Corridor() override {}
    inline std::string  getName() override { return "Corridor"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::CORRIDOR; }
};

class Quarter: public RoomType {
public: 
    ~Quarter() override {}
    inline std::string  getName() override { return "Quarter"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::QUARTER; }
};

class Bridge: public RoomType {
public: 
    ~Bridge() override {}
    inline std::string  getName() override { return "Bridge"; }
    inline RoomTypeEnum getType() override { return RoomTypeEnum::BRIDGE; }
};
