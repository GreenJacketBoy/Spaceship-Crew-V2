#ifndef ASSOCIATED_ROOMS_HPP
#define ASSOCIATED_ROOMS_HPP

#include <cstddef>
#include <optional>
#include "crew_member_moved_event.hpp"

// Class so that the attributes are read-only, only writable through the event handler methods
class AssociatedRooms : public CrewMemberMovedSubscriber {
public: 
    inline const std::optional<size_t> &getCurrentRoom() { return this->currentRoom; }
    void handleCrewMemberMoved(CrewMemberMovedPayload &payload) override;

private:
    std::optional<size_t> currentRoom;
};

#endif // !ASSOCIATED_ROOMS_HPP
