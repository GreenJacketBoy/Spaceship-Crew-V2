#include "create_crew_member_event.hpp"
#include "crew_member.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <qhashfunctions.h>
#include <qvariant.h>
#include <utility>
#include <vector>
#include "crew_member_moved_event.hpp"
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
    std::optional<size_t> optionalCurrentRoomId,
    QList<Skill> *skills // simple pointer because Qt doesn't know references nor const
) {
    auto &spaceShip = GameState::getInstance().getSpaceShip();
    if (!spaceShip) return;

    std::vector<Skill> skillsVector;
    skillsVector.reserve(skills->size());

    for (const auto &skill : *skills) {
        skillsVector.push_back(skill);
    }
    
    auto crewMember = std::unique_ptr<CrewMember>(new CrewMember(
        name.toStdString(),
        title.toStdString(),
        skillsVector
    ));

    size_t crewMemberId = crewMember->getId();
    auto crewMap = util::getCrewList();
    if (!crewMap) {
        std::cout << "Warning : crewMap undefined in CreateCrewMemberEvent\n";
        return;
    }
    crewMap.value()->insert({crewMemberId, std::move(crewMember)});
    CrewMemberMovedPayload payload = {
        crewMemberId,
        std::nullopt,
        optionalCurrentRoomId,
    };
    if (optionalCurrentRoomId) GameState::getInstance().getEventManager().get()->getCrewMemberMovedEvent().emitEvent(payload);
    // moved event must be sent before this one, otherwise the models getting updated will not have up to date information

    this->emitEvent(crewMemberId);
}
