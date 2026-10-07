#include "room_type_model.hpp"
#include "q_variant_special_type.hpp"
#include <iostream>
#include <qvariant.h>
#include "room_type.hpp"

int RoomTypeModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

int RoomTypeModel::rowCount(const QModelIndex &parent) const {
    return AMOUNT_OF_ROOM_TYPES;
}

QVariant RoomTypeModel::data(const QModelIndex &index, int role) const {
    if (index.row() > AMOUNT_OF_ROOM_TYPES - 1) {
        std::cout << "Warning in RoomListModel, requested row's index is higher than there are Room Types (row " << index.row() << " but " << AMOUNT_OF_ROOM_TYPES << " types\n";
        return QVariant();
    }
    RoomType roomType = util::createRoomTypeFromEnum(static_cast<RoomTypeEnum>(index.row()));
    switch (role) {
        case Text: return QVariant(roomType.getName());
        case Value: return util::QVariantSpecialType<RoomTypeEnum>(roomType.getType());
    }

    return QVariant();
}

QHash<int, QByteArray> RoomTypeModel::roleNames() const {
    return {
        { Text, "text"},
        { Value, "value"},
    };
}
