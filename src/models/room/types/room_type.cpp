#include "room_type.hpp"
#include "bridge.hpp"
#include "corridor.hpp"
#include "medbay.hpp"
#include "quarter.hpp"

// Compile time guarantee that all enums from RoomTypeEnum are handled damn I'm proud of that one
RoomType util::createRoomTypeFromEnum(RoomTypeEnum type) {
    switch (type) {
        case RoomTypeEnum::CORRIDOR: return Corridor();
        case RoomTypeEnum::BRIDGE: return Bridge();
        case RoomTypeEnum::MEDBAY: return Medbay();
        case RoomTypeEnum::QUARTER: return Quarter();
    }
}