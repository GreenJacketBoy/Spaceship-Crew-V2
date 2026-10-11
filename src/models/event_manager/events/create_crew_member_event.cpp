#include "create_crew_member_event.hpp"
#include "crew_member.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <qhashfunctions.h>
#include <vector>
#include "game_state.hpp"
#include "get_crew_list.hpp"

void CreateCrewMemberEvent::emitEvent(size_t &crewMemberId) {
    for (auto subscriber : this->subscribers) {
        subscriber->handleCrewMemberCreated(crewMemberId);
    }
}

void CreateCrewMemberEvent::createCrewMember(
    QString name,
    QString title,
    QList<size_t> skills // TODO: imlement choice of skills
) {
    auto &spaceShip = GameState::getInstance().getSpaceShip();
    if (!spaceShip) return;
    
    auto crewMember = std::unique_ptr<CrewMember>(new CrewMember(
        name.toStdString(),
        title.toStdString(),
        {}
    ));

    size_t crewMemberId = crewMember->getId();
    auto crewMap = util::getCrewList();
    if (!crewMap) {
        std::cout << "Warning : crewMap undefined in CreateCrewMemberEvent\n";
        return;
    }
    crewMap.value()->insert({crewMemberId, std::move(crewMember)});

    this->emitEvent(crewMemberId);
}
