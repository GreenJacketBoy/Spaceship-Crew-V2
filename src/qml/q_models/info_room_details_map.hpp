#ifndef INFO_ROOM_DETAILS_MAP_HPP
#define INFO_ROOM_DETAILS_MAP_HPP

#include "crew_member_moved_event.hpp"
#include "room_selected_event.hpp"
#include <QQmlPropertyMap>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>
#include <cstddef>

class InfoRoomDetailsMap : public QQmlPropertyMap, public RoomSelectedSubscriber, public CrewMemberMovedSubscriber {
    Q_OBJECT
public:
    explicit InfoRoomDetailsMap(QObject *parent = nullptr);

    void handleRoomSelected(size_t &roomId) override;

    void handleCrewMemberMoved(CrewMemberMovedPayload &payload) override;

    void triggerSubscriptions();

private:
    std::optional<size_t> roomId;
};

#endif // !INFO_ROOM_DETAILS_MAP_HPP
