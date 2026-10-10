#ifndef ROOM_LIST_MODEL_HPP
#define ROOM_LIST_MODEL_HPP

#include <cstddef>
#include "create_room_event.hpp"
#include <QAbstractTableModel>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class RoomListModel : public QAbstractTableModel, public CreateRoomSubscriber {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleRoomCreated(size_t &payload) override;

    void triggerSubscriptions();

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CrewCapacityRole,
        StorageCapacityRole,
        SizeRole,
        TypeRole,
    };
};

#endif // !ROOM_LIST_MODEL_HPP
