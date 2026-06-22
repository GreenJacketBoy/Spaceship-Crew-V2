#include <memory>
#include <set>
#include <cstddef>
#include <string>
#include <vector>
#include "room_type.hpp"

class Room {
    public: 
    Room(
        const std::string &name,
        size_t crewCapacity,
        size_t storageCapacity,
        size_t size,
        std::unique_ptr<RoomType> type,
        const std::vector<size_t> &adjacentRoomsIds
    );

    inline size_t       getId()              { return this->id;               }
    inline std::string  getName()            { return this->name;             }
    inline RoomTypeEnum getType()            { return this->type->getType();   }
    inline std::string  getTypeName()        { return this->type->getName();   }
    inline size_t       getSize()            { return this->size;             }
    inline size_t       getStorageCapacity() { return this->storageCapacity;  }
    inline size_t       getCrewCapacity()    { return this->crewCapacity;     }
    inline auto         getAdjacentRooms()   { return this->adjacentRoomsIds; }

    inline bool addAdjacentRoom(const size_t &roomId) {
        return this->adjacentRoomsIds.insert(roomId).second;
    }

    inline bool removeAdjacentRoom(const size_t &roomId) {
        return this->adjacentRoomsIds.extract(roomId).empty();
    }

    inline bool isRoomAdjacent(const size_t &roomId) {
        return this->adjacentRoomsIds.contains(roomId);
    }

private:
    size_t        id;
    std::string   name;
    size_t        crewCapacity;
    size_t        storageCapacity;
    size_t        size;
    inline static size_t next_id = 0;
    std::unique_ptr<RoomType> type;
    std::set<size_t> adjacentRoomsIds;
};
