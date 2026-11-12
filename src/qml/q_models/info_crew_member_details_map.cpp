#include "selected_crew_member_id.hpp"
#include "info_crew_member_details_map.hpp"
#include "get_crew_list.hpp"
#include "get_crew_member.hpp"
#include "get_room.hpp"
#include "q_variant_special_type.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qvariant.h>

InfoCrewMemberDetailsMap::InfoCrewMemberDetailsMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert("id",          QVariant());
    insert("name",        QVariant());
    insert("title",       QVariant());
    insert("currentRoom", QVariant());
}

void InfoCrewMemberDetailsMap::handleCrewMemberSelected(size_t &crewMemberId) {
    auto optionalCrewMember = util::getCrewMember(crewMemberId);
    if (!optionalCrewMember) return;
    auto crewMember = optionalCrewMember.value();

    insert("id", util::qVariantSizeT(crewMember->getId()));
    insert("name", QVariant(QString::fromStdString(crewMember->getName())));
    insert("title", QVariant(QString::fromStdString(crewMember->getTitle())));

    this->updateCurrentRoom(crewMember->getCurrentRoomId());
}

void InfoCrewMemberDetailsMap::handleCrewMemberMoved(CrewMemberMovedPayload &payload) {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    if (!selectedCrewMemberId || selectedCrewMemberId.value() != payload.crewMemberId) return;
    this->updateCurrentRoom(payload.toRoomId);
}

void InfoCrewMemberDetailsMap::updateCurrentRoom(const std::optional<size_t> &optionalRoomId) {
    if (!optionalRoomId) {
        insert("currentRoom", QVariant("Not in a room"));
        return;
    }
    auto optionalRoom = util::getRoom(optionalRoomId.value());
    if (!optionalRoom) return; // TODO: log a warning
    auto room = optionalRoom.value();

    insert("currentRoom", QVariant(std::format("#{} {} ({})", room->getId(), room->getName(), room->getTypeName()).c_str()));
}

void InfoCrewMemberDetailsMap::handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    if (selectedCrewMemberId && selectedCrewMemberId.value() == payload.crewMemberId) {
        insert("title", QVariant(QString(payload.title)));
    }
}

void InfoCrewMemberDetailsMap::handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    if (selectedCrewMemberId && selectedCrewMemberId.value() == payload.crewMemberId) {
        insert("name", QVariant(QString(payload.name)));
    }
}

void InfoCrewMemberDetailsMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberMovedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberTitleUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberNameUpdatedEvent().subscribe(*this);
}
