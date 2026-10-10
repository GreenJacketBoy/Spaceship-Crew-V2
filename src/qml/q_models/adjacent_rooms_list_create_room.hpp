#ifndef ADJACENT_ROOMS_LIST_CREATE_ROOM_HPP
#define ADJACENT_ROOMS_LIST_CREATE_ROOM_HPP

#include <cstddef>
#include "create_room_event.hpp"
#include "room.hpp"
#include <QAbstractTableModel>
#include <qhashfunctions.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <qvariant.h>

enum RoomModelRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    TypeRole,
};

class AdjacentRoomsListCreateRoomModel : public QAbstractTableModel {
Q_OBJECT
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setRoomList(std::map<size_t, std::unique_ptr<Room>> &roomList);

    Q_INVOKABLE QList<size_t> getAdjacentRooms() { return this->adjacentRooms; };

public slots: 
    void adjacentRoomAddedCreateForm(size_t roomId);
    void adjacentRoomRemovedCreateForm(size_t roomId);

private:
    QList<size_t> adjacentRooms;
};

#endif // !ADJACENT_ROOMS_LIST_CREATE_ROOM_HPP
