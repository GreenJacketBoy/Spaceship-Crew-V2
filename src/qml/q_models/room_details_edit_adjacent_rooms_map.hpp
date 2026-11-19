#ifndef ROOM_DETAILS_EDIT_ADJACENT_ROOMS_MAP_HPP
#define ROOM_DETAILS_EDIT_ADJACENT_ROOMS_MAP_HPP

#include "room_selected_event.hpp"
#include "room_unselected_event.hpp"
#include <QQmlPropertyMap>
#include <cstddef>

class RoomDetailsEditAdjacentRoomsMap : public QQmlPropertyMap, public RoomSelectedSubscriber, public RoomUnselectedSubscriber {
    Q_OBJECT
public:
    explicit RoomDetailsEditAdjacentRoomsMap(QObject *parent = nullptr);

    void handleRoomSelected(size_t &roomId) override;

    void handleRoomUnselected(size_t &roomId) override;

    void triggerSubscriptions();

public slots:
    void edit();
    void add(size_t adjacentRoomId);
    void remove(size_t adjacentRoomId);
    void cancel();

};

#endif // !ROOM_DETAILS_EDIT_ADJACENT_ROOMS_MAP_HPP
