#include "crew_member_selected_event.hpp"
#include "game_state.hpp"
#include "selected_crew_member_id.hpp"

void CrewMemberSelectedEvent::emitEvent(size_t &crewMemberId) {
    GameState::getInstance().getSelectedEntitiesMap()->handleCrewMemberSelected(crewMemberId);

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberSelected(crewMemberId);
    }
}

void CrewMemberSelectedEvent::selectCrewMember(size_t crewMemberId) {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    bool isAlreadySelected = selectedCrewMemberId && selectedCrewMemberId.value() == crewMemberId;

    if (isAlreadySelected) GameState::getInstance().getEventManager()->getCrewMemberUnselectedEvent().emitEvent(crewMemberId);
    else this->emitEvent(crewMemberId);
}
