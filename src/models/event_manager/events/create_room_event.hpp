#ifndef CREATE_ROOM_EVENT_HPP
#define CREATE_ROOM_EVENT_HPP

#include "event_template.hpp"
#include "room_type.hpp"
#include <cstddef>
#include <qlist.h>
#include <qobject.h>
#include <qtmetamacros.h>

class Room; // Forward declaration. 
// I'm putting a comment because it's the first time I use it, and I'll cringe in a year because it's obvious it is.
// :sunglasses_hiding_tears:

class CreateRoomSubscriber {
public: 
    virtual void handleRoomCreated(size_t &payload) = 0;
};

class CreateRoomEvent : public QObject, public Event<size_t, CreateRoomSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &roomId) override;

public slots:
    void createRoom(
        QString name,
        QString crewCapacity,
        QString storageCapacity,
        QString size,
        RoomTypeEnum type,
        QList<size_t> adjacentRoomsIds
    );
};

#endif // !CREATE_ROOM_EVENT_HPP
