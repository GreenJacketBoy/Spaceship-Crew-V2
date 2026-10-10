#ifndef GET_ROOM_HPP
#define GET_ROOM_HPP

#include <cstddef>
#include <optional>

class Room; // Forward Declaration

namespace util {
    /** No except getRoom */
    std::optional<Room *> getRoom(size_t roomId) noexcept;
}

#endif // !GET_ROOM_HPP
