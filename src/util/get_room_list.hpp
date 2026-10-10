#ifndef GET_ROOM_LIST_HPP
#define GET_ROOM_LIST_HPP

#include <map>
#include <memory>
#include <optional>

class Room; // Forward Declaration

namespace util {
    /** No except getRoom */
    std::optional<std::map<size_t, std::unique_ptr<Room>> *> getRoomList() noexcept;
}

#endif // !GET_ROOM_LIST_HPP
