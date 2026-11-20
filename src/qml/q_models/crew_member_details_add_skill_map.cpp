#include "crew_member_details_add_skill_map.hpp"
#include "crew_member.hpp"
#include "game_state.hpp"
#include "get_crew_member.hpp"
#include "selected_crew_member_id.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qvariant.h>

CrewMemberDetailsAddSkillMap::CrewMemberDetailsAddSkillMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert("isEditing", QVariant(false));
}

void CrewMemberDetailsAddSkillMap::handleCrewMemberSelected(size_t &crewMemberId) {
    insert("isEditing", QVariant(false));
}

void CrewMemberDetailsAddSkillMap::handleCrewMemberUnselected(size_t &crewMemberId) {
    insert("isEditing", QVariant(false));
}

void CrewMemberDetailsAddSkillMap::edit() {
    insert("isEditing", QVariant(true));
}

void CrewMemberDetailsAddSkillMap::cancel() {
    insert("isEditing", QVariant(false));
}

void CrewMemberDetailsAddSkillMap::save(SkillType skillType, QString levelString) {
    auto optionalCrewMember = util::getCrewMember(util::selectedCrewMemberId());
    if (!optionalCrewMember) return;
    CrewMember *crewMember = optionalCrewMember.value();

    size_t level = -1;
    auto stream = std::stringstream(levelString.toStdString());
    stream >> level;

    CrewMemberSkillUpdatedPayload payload = {
        crewMember->getId(),
        skillType, 
        level,
        crewMember->getSkillLevel(skillType),
    };
    GameState::getInstance().getEventManager()->getCrewMemberSkillUpdatedEvent().emitEvent(payload);
    insert("isEditing", QVariant(false));
}

void CrewMemberDetailsAddSkillMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberUnselectedEvent().subscribe(*this);
}
