#ifndef ADJACENT_ROOM_LIST_ROOM_DETAILS_HPP
#define ADJACENT_ROOM_LIST_ROOM_DETAILS_HPP

#include <cstddef>
#include "create_room_event.hpp"
#include "room_selected_event.hpp"
#include <QAbstractTableModel>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class AdjacentRoomListRoomDetailsModel : public QAbstractTableModel, public CreateRoomSubscriber, public RoomSelectedSubscriber {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleRoomCreated(size_t &roomId) override;

    void handleRoomSelected(size_t &roomId) override;

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

    std::optional<size_t> roomId;
};

#endif // !ADJACENT_ROOM_LIST_ROOM_DETAILS_HPP
