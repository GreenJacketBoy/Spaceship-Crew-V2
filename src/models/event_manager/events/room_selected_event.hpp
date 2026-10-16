#ifndef ROOM_SELECTED_EVENT_HPP
#define ROOM_SELECTED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <qobject.h>
#include <qtmetamacros.h>

class Room;

class RoomSelectedSubscriber {
public: 
    virtual void handleRoomSelected(size_t &payload) = 0;
};

class RoomSelectedEvent : public QObject, public Event<size_t, RoomSelectedSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &roomId) override;

public slots:
    inline void selectRoom(size_t roomId) { this->emitEvent(roomId); };
};

#endif // !ROOM_SELECTED_EVENT_HPP
