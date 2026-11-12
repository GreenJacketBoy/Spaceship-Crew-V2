#include "crew_member_unselected_event.hpp"
#include "game_state.hpp"
#include <qlogging.h>

void CrewMemberUnselectedEvent::emitEvent(size_t &crewMemberId) {
    GameState::getInstance().getSelectedEntitiesMap()->handleCrewMemberUnselected(crewMemberId);

    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberUnselected(crewMemberId);
    }
}
