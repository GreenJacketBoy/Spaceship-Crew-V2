#ifndef GET_ROOM_LIST_HPP
#define GET_ROOM_LIST_HPP

#include <map>
#include <memory>
#include <optional>

class CrewMember; // Forward Declaration

namespace util {
    /** No except getRoom */
    std::optional<std::map<size_t, std::unique_ptr<CrewMember>> *> getCrewList() noexcept;
}

#endif // !GET_ROOM_LIST_HPP
