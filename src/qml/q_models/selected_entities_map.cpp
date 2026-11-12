#include "selected_entities_map.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qvariant.h>

SelectedEntitiesMap::SelectedEntitiesMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert(LAST_SELECTED, QVariant(SelectedEntity::NONE));
}

void SelectedEntitiesMap::handleRoomSelected(size_t &roomId) {
    this->lastSelected = SelectedEntity::ROOM;
    this->roomId = roomId;
    insert(LAST_SELECTED, QVariant(SelectedEntity::ROOM));
}

void SelectedEntitiesMap::handleRoomUnselected(size_t &roomId) {
    if (!this->roomId || this->roomId != roomId) return;

    this->lastSelected = this->crewMemberId ? SelectedEntity::CREW_MEMBER : SelectedEntity::NONE;
    this->roomId = std::nullopt;
    insert(LAST_SELECTED, QVariant(this->lastSelected));
}

void SelectedEntitiesMap::handleCrewMemberSelected(size_t &crewMemberId) {
    this->lastSelected = SelectedEntity::CREW_MEMBER;
    this->crewMemberId = crewMemberId;
    insert(LAST_SELECTED, QVariant(SelectedEntity::CREW_MEMBER));
}

void SelectedEntitiesMap::handleCrewMemberUnselected(size_t &crewMemberId) {
    if (!this->crewMemberId || this->crewMemberId != crewMemberId) return;

    this->lastSelected = this->roomId ? SelectedEntity::ROOM : SelectedEntity::NONE;
    this->crewMemberId = std::nullopt;
    insert(LAST_SELECTED, QVariant(this->lastSelected));
}
