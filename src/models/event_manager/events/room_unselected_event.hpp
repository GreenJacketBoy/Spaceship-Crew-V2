#ifndef ROOM_UNSELECTED_EVENT_HPP
#define ROOM_UNSELECTED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <qobject.h>
#include <qtmetamacros.h>

class RoomUnselectedSubscriber {
public: 
    virtual void handleRoomUnselected(size_t &payload) = 0;
};

class RoomUnselectedEvent : public QObject, public Event<size_t, RoomUnselectedSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &roomId) override;

public slots:
    inline void selectRoom(size_t roomId) { this->emitEvent(roomId); };
};

#endif // !ROOM_UNSELECTED_EVENT_HPP
