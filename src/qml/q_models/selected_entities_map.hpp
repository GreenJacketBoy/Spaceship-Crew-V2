#ifndef SELECTED_ENTITIES_MAP_HPP
#define SELECTED_ENTITIES_MAP_HPP

#include "crew_member_selected_event.hpp"
#include "room_selected_event.hpp"
#include <QQmlPropertyMap>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>
#include <cstddef>

static const char *LAST_SELECTED = "lastSelected";

enum SelectedEntity {
    ROOM = 0,
    CREW_MEMBER,
    NONE, // NONE should stay at the end so that its index is associated to nothing
};

class SelectedEntitiesMap : public QQmlPropertyMap, public RoomSelectedSubscriber, public CrewMemberSelectedSubscriber {
    Q_OBJECT
public:
    explicit SelectedEntitiesMap(QObject *parent = nullptr);

    void handleRoomSelected(size_t &roomId) override;

    void handleCrewMemberSelected(size_t &payload) override;

    void triggerSubscriptions();

private:
    std::optional<size_t> roomId;
};

#endif // !SELECTED_ENTITIES_MAP_HPP
