#include "selected_entities_map.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <qobject.h>
#include <qvariant.h>

SelectedEntitiesMap::SelectedEntitiesMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert(LAST_SELECTED, QVariant(SelectedEntity::NONE));
}

void SelectedEntitiesMap::handleRoomSelected(size_t &roomId) {
    insert(LAST_SELECTED, QVariant(SelectedEntity::ROOM));
}

void SelectedEntitiesMap::handleCrewMemberSelected(size_t &crewMemberId) {
    insert(LAST_SELECTED, QVariant(SelectedEntity::CREW_MEMBER));
}

void SelectedEntitiesMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
}
