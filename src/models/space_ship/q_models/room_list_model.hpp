#ifndef ROOM_LIST_MODEL_HPP
#define ROOM_LIST_MODEL_HPP

#include <cstddef>
#include <optional>
#include "room.hpp"
#include <QAbstractTableModel>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class RoomListModel : public QAbstractTableModel {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setRoomList(std::map<size_t, std::unique_ptr<Room>> &roomList);

    /** Because QVariant doesn't have a constructor for size_t */
    constexpr QVariant qVariantSizeT(const size_t number) const;

private:
    enum RoomModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CrewCapacityRole,
        StorageCapacityRole,
        SizeRole,
        TypeRole,
    };

    std::optional<std::map<size_t, std::unique_ptr<Room>>*> roomList;
};

#endif // !ROOM_LIST_MODEL_HPP
