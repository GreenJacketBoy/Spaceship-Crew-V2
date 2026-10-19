#ifndef GET_CREW_MEMBER_HPP
#define GET_CREW_MEMBER_HPP

#include <cstddef>
#include <optional>

class CrewMember; 

namespace util {
    /** No except getCrewMember */
    std::optional<CrewMember *> getCrewMember(size_t crewMemberId) noexcept;
}

#endif // !GET_CREW_MEMBER_HPP
