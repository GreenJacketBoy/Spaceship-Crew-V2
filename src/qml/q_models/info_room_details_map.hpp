#ifndef INFO_ROOM_DETAILS_MAP_HPP
#define INFO_ROOM_DETAILS_MAP_HPP

#include "crew_member_moved_event.hpp"
#include "room_crew_capacity_updated_event.hpp"
#include "room_name_updated_event.hpp"
#include "room_selected_event.hpp"
#include "room_size_updated_event.hpp"
#include "room_storage_capacity_updated_event.hpp"
#include "room_type_updated_event.hpp"
#include <QQmlPropertyMap>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>
#include <cstddef>

class InfoRoomDetailsMap : public QQmlPropertyMap, public RoomSelectedSubscriber, public CrewMemberMovedSubscriber, public RoomNameUpdatedSubscriber, public RoomCrewCapacityUpdatedSubscriber, public RoomTypeUpdatedSubscriber, public RoomStorageCapacityUpdatedSubscriber, public RoomSizeUpdatedSubscriber {
    Q_OBJECT
public:
    explicit InfoRoomDetailsMap(QObject *parent = nullptr);

    void handleRoomSelected(size_t &roomId) override;

    void handleCrewMemberMoved(CrewMemberMovedPayload &payload) override;

    void handleRoomNameUpdated(RoomNameUpdatedPayload &payload) override;

    void handleRoomCrewCapacityUpdated(RoomCrewCapacityUpdatedPayload &payload) override;

    void handleRoomStorageCapacityUpdated(RoomStorageCapacityUpdatedPayload &payload) override;

    void handleRoomSizeUpdated(RoomSizeUpdatedPayload &payload) override;

    void handleRoomTypeUpdated(RoomTypeUpdatedPayload &payload) override;

    void triggerSubscriptions();

private:
    std::optional<size_t> roomId;
};

#endif // !INFO_ROOM_DETAILS_MAP_HPP
