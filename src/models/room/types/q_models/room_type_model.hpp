#ifndef ROOM_TYPE_MODEL_HPP
#define ROOM_TYPE_MODEL_HPP

#include <QAbstractTableModel>
#include <qabstractitemmodel.h>
#include <qhashfunctions.h>
#include <qnamespace.h>

class RoomTypeModel : public QAbstractListModel {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    enum RoomListModelRoles {
        Text = Qt::UserRole + 1,
        Value,
    };
};

#endif // !ROOM_TYPE_MODEL_HPP
