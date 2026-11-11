#include "info_room_details_map.hpp"
#include "q_variant_special_type.hpp"
#include "get_room.hpp"
#include "game_state.hpp"
#include <qlogging.h>
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
    this->roomId = roomId;
    auto optionalRoom = util::getRoom(this->roomId.value());
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
    if (!this->roomId) return;

    if (!payload.toRoomId && !payload.fromRoomId) return;
    if (payload.fromRoomId.value() != this->roomId.value() &&  payload.fromRoomId.value() != this->roomId.value()) return;

    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("currentCrewAmount", util::qVariantSizeT(room->getCrewMembersInRoom().size()));
}

void InfoRoomDetailsMap::handleRoomNameUpdated(RoomNameUpdatedPayload &payload) {
    if (!this->roomId || this->roomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("name", QVariant(QString::fromStdString(room->getName())));
}

void InfoRoomDetailsMap::handleRoomCrewCapacityUpdated(RoomCrewCapacityUpdatedPayload &payload) {
    qDebug() << "check";
    if (!this->roomId || this->roomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("crewCapacity", util::qVariantSizeT(room->getCrewCapacity()));
}

void InfoRoomDetailsMap::handleRoomStorageCapacityUpdated(RoomStorageCapacityUpdatedPayload &payload) {
    if (!this->roomId || this->roomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("storageCapacity", util::qVariantSizeT(room->getStorageCapacity()));
}

void InfoRoomDetailsMap::handleRoomSizeUpdated(RoomSizeUpdatedPayload &payload) {
    if (!this->roomId || this->roomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    insert("size", util::qVariantSizeT(room->getSize()));
}

void InfoRoomDetailsMap::handleRoomTypeUpdated(RoomTypeUpdatedPayload &payload) {
    if (!this->roomId || this->roomId.value() != payload.roomId)
        return;
    auto optionalRoom = util::getRoom(this->roomId.value());
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
