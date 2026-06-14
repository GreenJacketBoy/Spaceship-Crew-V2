#include <cstddef>
#include <string>
#include "room_type.hpp"

class Room {
public: 
    Room(
        const std::string &name,
        size_t crewCapacity,
        size_t storageCapacity,
        size_t size,
        RoomType *type
    );

    inline std::string  getName()            { return this->name;            }
    inline RoomTypeEnum getType()            { return this->type->getType(); }
    inline std::string  getTypeName()        { return this->type->getName(); }
    inline size_t       getSize()            { return this->size;            }
    inline size_t       getStorageCapacity() { return this->storageCapacity; }
    inline size_t       getCrewCapacity()    { return this->crewCapacity;    }

private:
    std::string name;
    size_t      crewCapacity;
    size_t      storageCapacity;
    size_t      size;
    RoomType   *type;
};
