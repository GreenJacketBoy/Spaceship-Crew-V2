#ifndef ROOM_HPP
#define ROOM_HPP

#include <set>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>
#include "crew_member_deleted_event.hpp"
#include "crew_member_moved_event.hpp"
#include "room_type.hpp"

class Room : public CrewMemberMovedSubscriber, public CrewMemberDeletedSubscriber {
    public: 
    Room(
        std::string &&name,
        size_t crewCapacity,
        size_t storageCapacity,
        size_t size,
        RoomTypeEnum type,
        const std::vector<size_t> &adjacentRoomsIds
    );

    inline size_t       getId()              { return this->id;               }
    inline const std::string &getName()      { return this->name;             }
    inline RoomTypeEnum getType()            { return this->type.getType();  }
    inline const char*  getTypeName()        { return this->type.getName();  }
    inline size_t       getSize()            { return this->size;             }
    inline size_t       getStorageCapacity() { return this->storageCapacity;  }
    inline size_t       getCrewCapacity()    { return this->crewCapacity;     }
    inline auto        &getAdjacentRooms()   { return this->adjacentRoomsIds; }
    inline const auto  &getCrewMembersInRoom() { return this->crewMembersInRoom; }

    inline void setName(const std::string &name) { this->name = name; }
    inline void setName(std::string &&name)      { this->name = name; }

    inline void setRoomType(const RoomType &type) { this->type = type; }
    inline void setRoomType(RoomType &&type)      { this->type = type; }

    inline void setSize(size_t size) { this->size = size; }
    inline void setCrewCapacity(size_t crewCapacity) { this->crewCapacity = crewCapacity; }
    inline void setStorageCapacity(size_t storageCapacity) { this->storageCapacity = storageCapacity; }

    inline bool addAdjacentRoom(const size_t &roomId) {
        return this->adjacentRoomsIds.insert(roomId).second;
    }

    inline bool removeAdjacentRoom(const size_t &roomId) {
        return this->adjacentRoomsIds.extract(roomId).empty();
    }

    inline bool isRoomAdjacent(const size_t &roomId) {
        return this->adjacentRoomsIds.contains(roomId);
    }

    void handleCrewMemberMoved(CrewMemberMovedPayload &payload) override;
    void handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) override;

private:
    size_t        id;
    std::string   name;
    size_t        crewCapacity;
    size_t        storageCapacity;
    size_t        size;
    inline static size_t next_id = 0;
    RoomType type;
    std::set<size_t> adjacentRoomsIds;
    std::set<size_t> crewMembersInRoom;
};

#endif // !ROOM_HPP
