#include "edit_info_room_details_map.hpp"
#include "get_room.hpp"
#include "q_variant_special_type.hpp"
#include "game_state.hpp"
#include "room_name_updated_event.hpp"
#include "room_type_updated_event.hpp"
#include "room_type.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qvariant.h>
#include <string>

EditInfoRoomDetailsMap::EditInfoRoomDetailsMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert("id",          QString());
    insert("name",        QString());
    insert("type", util::QVariantSpecialType(RoomTypeEnum::BRIDGE)); // The default value does not matter
    insert("size", util::qVariantSizeT(0));
    insert("isEditing",   QVariant(false));
}

void EditInfoRoomDetailsMap::handleRoomSelected(size_t &crewMemberId) {
    this->roomId = crewMemberId;
    this->resetToCurrentValues();
}

void EditInfoRoomDetailsMap::resetToCurrentValues() {
    std::optional<Room *> optionalRoom;
    if (!this->roomId || !(optionalRoom = util::getRoom(this->roomId.value()))) {
        insert("id",          QString());
        insert("name",        QString());
        insert("type", util::QVariantSpecialType(RoomTypeEnum::BRIDGE));
        insert("size", util::qVariantSizeT(0));
        insert("crewCapacity", util::qVariantSizeT(0));
        insert("storageCapacity", util::qVariantSizeT(0));
        return;
    }

    auto room = optionalRoom.value();

    insert("id", util::qVariantSizeT(room->getId()));
    // First setting to garbage values before actually setting them, because if:
    // - UI changes the value
    // - Cancel is clicked
    // - The map still has the old values, which are different from the ones on the UI (there's no 2way binding)
    // - The old values are re-inserted, but because they are the same, the changes are not propagated to the UI
    // So setting it to another value before forces propagation to the UI
    insert("name", QString());
    insert("name", QVariant(QString::fromStdString(room->getName())));
    insert("type", util::QVariantSpecialType(static_cast<RoomTypeEnum>(-1)));
    insert("type", util::QVariantSpecialType(room->getType()));
    insert("size", util::qVariantSizeT(0));
    insert("size", util::qVariantSizeT(room->getSize()));
    insert("crewCapacity", util::qVariantSizeT(0));
    insert("crewCapacity", util::qVariantSizeT(room->getCrewCapacity()));
    insert("storageCapacity", util::qVariantSizeT(0));
    insert("storageCapacity", util::qVariantSizeT(room->getStorageCapacity()));
}

void EditInfoRoomDetailsMap::save(QString name, QString crewCapacityAsString, QString storageCapacityAsString, QString sizeAsString, RoomTypeEnum roomType) {
    if (!this->roomId) return;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return;
    auto room = optionalRoom.value();

    std::string nameString = name.toStdString();
    size_t crewCapacity = -1;
    size_t storageCapacity = -1;
    size_t size = -1;
    auto stream = std::stringstream(crewCapacityAsString.toStdString());
    stream >> crewCapacity;
    stream.clear(); stream.str(storageCapacityAsString.toStdString());
    stream >> storageCapacity;
    stream.clear(); stream.str(sizeAsString.toStdString());
    stream >> size;

    if (nameString != room->getName()) {
        RoomNameUpdatedPayload payload = {room->getId(), nameString.c_str()};
        GameState::getInstance().getEventManager()->getRoomNameUpdatedEvent().emitEvent(payload);
    }
    if (roomType != room->getType()) {
        RoomTypeUpdatedPayload payload = {room->getId(), util::createRoomTypeFromEnum(roomType)};
        GameState::getInstance().getEventManager()->getRoomTypeUpdatedEvent().emitEvent(payload);
    }
    if (storageCapacity != room->getStorageCapacity()) {
        RoomStorageCapacityUpdatedPayload payload = {room->getId(), storageCapacity};
        GameState::getInstance().getEventManager()->getRoomStorageCapacityUpdatedEvent().emitEvent(payload);
    }
    if (crewCapacity != room->getCrewCapacity()) {
        RoomCrewCapacityUpdatedPayload payload = {room->getId(), crewCapacity};
        GameState::getInstance().getEventManager()->getRoomCrewCapacityUpdatedEvent().emitEvent(payload);
    }
    if (size != room->getSize()) {
        RoomSizeUpdatedPayload payload = {room->getId(), size};
        GameState::getInstance().getEventManager()->getRoomSizeUpdatedEvent().emitEvent(payload);
    }
    this->resetToCurrentValues();
    insert("isEditing", QVariant(false));
}

void EditInfoRoomDetailsMap::cancel() {
    this->resetToCurrentValues();
    insert("isEditing", QVariant(false));
}

void EditInfoRoomDetailsMap::openEditMenu() {
    this->resetToCurrentValues();
    insert("isEditing", QVariant(true));
}

void EditInfoRoomDetailsMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
}
