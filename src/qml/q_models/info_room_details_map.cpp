#include "info_room_details_map.hpp"
#include "q_variant_special_type.hpp"
#include "get_room.hpp"
#include "game_state.hpp"
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

void InfoRoomDetailsMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberMovedEvent().subscribe(*this);
}
