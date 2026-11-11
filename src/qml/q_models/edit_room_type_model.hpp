#ifndef EDIT_ROOM_TYPE_MODEL_HPP
#define EDIT_ROOM_TYPE_MODEL_HPP

#include <QAbstractTableModel>
#include <qabstractitemmodel.h>
#include <qhashfunctions.h>
#include <qnamespace.h>

class EditRoomTypeModel : public QAbstractListModel {
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    enum RoomListModelRoles {
        Text = Qt::UserRole + 1,
        Value,
    };
};

#endif // !EDIT_ROOM_TYPE_MODEL_HPP
