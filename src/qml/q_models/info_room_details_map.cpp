#include "selected_room_id.hpp"
#include "info_room_details_map.hpp"
#include "q_variant_special_type.hpp"
#include "get_room.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <qobject.h>
#include <qvariant.h>

InfoRoomDetailsMap::InfoRoomDetailsMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert("id",                QVariant());
    insert("name",              QVariant());
    insert("crewCapacity",      QVariant());
    insert("currentCrewAmount", QVariant());
    insert("storageCapacity",   QVariant());
    insert("size",              QVariant());
    insert("type",              QVariant());
}

void InfoRoomDetailsMap::handleRoomSelected(size_t &roomId) {
    auto optionalRoom = util::getRoom(roomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("id", util::qVariantSizeT(room->getId()));
    insert("name", QVariant(QString::fromStdString(room->getName())));
    insert("crewCapacity", util::qVariantSizeT(room->getCrewCapacity()));
    insert("currentCrewAmount", util::qVariantSizeT(room->getCrewMembersInRoom().size()));
    insert("storageCapacity", util::qVariantSizeT(room->getStorageCapacity()));
    insert("size", util::qVariantSizeT(room->getSize()));
    insert("type", QVariant(room->getTypeName()));
}

void InfoRoomDetailsMap::handleCrewMemberMoved(CrewMemberMovedPayload &payload) {
    const auto optionalSelectedRoomId = util::selectedRoomId();
    if (!optionalSelectedRoomId) return;
    const size_t selectedRoomId = optionalSelectedRoomId.value();

    if (!payload.toRoomId && !payload.fromRoomId) return;
    if (payload.fromRoomId.value() != selectedRoomId &&  payload.fromRoomId.value() != selectedRoomId) return;

    auto optionalRoom = util::getRoom(selectedRoomId);
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("currentCrewAmount", util::qVariantSizeT(room->getCrewMembersInRoom().size()));
}

void InfoRoomDetailsMap::handleRoomNameUpdated(RoomNameUpdatedPayload &payload) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId || selectedRoomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(selectedRoomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("name", QVariant(QString::fromStdString(room->getName())));
}

void InfoRoomDetailsMap::handleRoomCrewCapacityUpdated(RoomCrewCapacityUpdatedPayload &payload) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId || selectedRoomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(selectedRoomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("crewCapacity", util::qVariantSizeT(room->getCrewCapacity()));
}

void InfoRoomDetailsMap::handleRoomStorageCapacityUpdated(RoomStorageCapacityUpdatedPayload &payload) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId || selectedRoomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(selectedRoomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("storageCapacity", util::qVariantSizeT(room->getStorageCapacity()));
}

void InfoRoomDetailsMap::handleRoomSizeUpdated(RoomSizeUpdatedPayload &payload) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId || selectedRoomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(selectedRoomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("size", util::qVariantSizeT(room->getSize()));
}

void InfoRoomDetailsMap::handleRoomTypeUpdated(RoomTypeUpdatedPayload &payload) {
    const auto selectedRoomId = util::selectedRoomId();
    if (!selectedRoomId || selectedRoomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(selectedRoomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("type", QVariant(room->getTypeName()));
}


void InfoRoomDetailsMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberMovedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomNameUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomCrewCapacityUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomStorageCapacityUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomTypeUpdatedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomSizeUpdatedEvent().subscribe(*this);
}
