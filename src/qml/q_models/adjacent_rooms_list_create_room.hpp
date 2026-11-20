#ifndef ADJACENT_ROOMS_LIST_CREATE_ROOM_HPP
#define ADJACENT_ROOMS_LIST_CREATE_ROOM_HPP

#include "room_deleted_event.hpp"
#include <cstddef>
#include <QAbstractTableModel>
#include <qabstractitemmodel.h>
#include <qhashfunctions.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <qvariant.h>

class AdjacentRoomsListCreateRoomModel : public QAbstractListModel, public RoomDeletedSubscriber {
Q_OBJECT
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void handleRoomDeleted(size_t &roomId) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QList<size_t> *getAdjacentRooms() { return &this->adjacentRooms; };

    void triggerSubscriptions();

public slots: 
    void adjacentRoomAddedCreateForm(size_t roomId);
    void adjacentRoomRemovedCreateForm(size_t roomId);

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TypeRole,
    };

    QList<size_t> adjacentRooms;
};

#endif // !ADJACENT_ROOMS_LIST_CREATE_ROOM_HPP
