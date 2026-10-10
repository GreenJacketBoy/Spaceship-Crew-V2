#ifndef ADD_ADJACENT_ROOM_MODEL_HPP
#define ADD_ADJACENT_ROOM_MODEL_HPP

#include "create_room_event.hpp"
#include <QAbstractTableModel>
#include <qabstractitemmodel.h>
#include <qhashfunctions.h>
#include <qnamespace.h>

class AddAdjacentRoomModel : public QAbstractListModel, public CreateRoomSubscriber {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleRoomCreated(size_t &payload) override;

    void triggerSubscriptions();

private:
    enum ModelRoles {
        Text = Qt::UserRole + 1,
        Value,
    };
};

#endif // !ADD_ADJACENT_ROOM_MODEL_HPP
