#ifndef ROOM_DELETED_EVENT_HPP
#define ROOM_DELETED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <qobject.h>
#include <qtmetamacros.h>

class RoomDeletedSubscriber {
public: 
    virtual void handleRoomDeleted(size_t &payload) = 0;
};

class RoomDeletedEvent : public QObject, public Event<size_t, RoomDeletedSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &payload) override;

public slots:
    void deleteRoom(size_t crewMemberId);
};

#endif // !ROOM_DELETED_EVENT_HPP
