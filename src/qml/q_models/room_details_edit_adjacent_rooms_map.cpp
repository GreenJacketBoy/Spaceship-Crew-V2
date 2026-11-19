#include "room_details_edit_adjacent_rooms_map.hpp"
#include "game_state.hpp"
#include "room_add_adjacent_room_event.hpp"
#include "room_remove_adjacent_room_event.hpp"
#include "selected_room_id.hpp"
#include <cstddef>
#include <optional>
#include <qlogging.h>
#include <qobject.h>
#include <qvariant.h>

RoomDetailsEditAdjacentRoomsMap::RoomDetailsEditAdjacentRoomsMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert("isEditing", QVariant(false));
}

void RoomDetailsEditAdjacentRoomsMap::handleRoomSelected(size_t &roomId) {
    insert("isEditing", QVariant(false));
}

void RoomDetailsEditAdjacentRoomsMap::handleRoomUnselected(size_t &roomId) {
    insert("isEditing", QVariant(false));
}

void RoomDetailsEditAdjacentRoomsMap::edit() {
    insert("isEditing", QVariant(true));
}

void RoomDetailsEditAdjacentRoomsMap::cancel() {
    insert("isEditing", QVariant(false));
}

void RoomDetailsEditAdjacentRoomsMap::add(size_t adjacentRoomId) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId) return;

    RoomAddAdjacentRoomPayload payload = {
        selectedRoomId.value(),
        adjacentRoomId,
    };
    GameState::getInstance().getEventManager()->getRoomAddAdjacentRoomEvent().emitEvent(payload);
    insert("isEditing", QVariant(false));
}

void RoomDetailsEditAdjacentRoomsMap::remove(size_t adjacentRoomId) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId) return;

    RoomRemoveAdjacentRoomPayload payload = {
        selectedRoomId.value(),
        adjacentRoomId,
    };
    GameState::getInstance().getEventManager()->getRoomRemoveAdjacentRoomEvent().emitEvent(payload);
}

void RoomDetailsEditAdjacentRoomsMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomUnselectedEvent().subscribe(*this);
}
