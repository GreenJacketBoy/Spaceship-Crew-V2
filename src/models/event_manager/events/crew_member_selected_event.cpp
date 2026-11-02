#include "crew_member_selected_event.hpp"

void CrewMemberSelectedEvent::emitEvent(size_t &crewMemberId) {
    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberSelected(crewMemberId);
    }
}
