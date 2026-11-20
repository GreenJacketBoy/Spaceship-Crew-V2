#ifndef GET_CREW_MEMBER_HPP
#define GET_CREW_MEMBER_HPP

#include <cstddef>
#include <optional>

class CrewMember; 

namespace util {
    /** No except getCrewMember */
    std::optional<CrewMember *> getCrewMember(size_t crewMemberId) noexcept;
    std::optional<CrewMember *> getCrewMember(const std::optional<size_t> &optionalCrewMemberId) noexcept;
}

#endif // !GET_CREW_MEMBER_HPP
