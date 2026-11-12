#ifndef SELECTED_ENTITIES_MAP_HPP
#define SELECTED_ENTITIES_MAP_HPP

#include "crew_member_selected_event.hpp"
#include "crew_member_unselected_event.hpp"
#include "room_selected_event.hpp"
#include "room_unselected_event.hpp"
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

class SelectedEntitiesMap : public QQmlPropertyMap, public RoomSelectedSubscriber, public CrewMemberSelectedSubscriber, public RoomUnselectedSubscriber, public CrewMemberUnselectedSubscriber {
    Q_OBJECT
public:
    explicit SelectedEntitiesMap(QObject *parent = nullptr);

    void handleRoomSelected(size_t &roomId) override;

    void handleRoomUnselected(size_t &roomId) override;
    
    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void handleCrewMemberUnselected(size_t &crewMemberId) override;

    void triggerSubscriptions() = delete; // all events for this class must be triggered manually, before the automatic ones

    auto getLastSelected() { return this->lastSelected; }
    auto getRoomId() { return this->roomId; }
    auto getCrewMemberId() { return this->crewMemberId; }

private:
    SelectedEntity lastSelected = SelectedEntity::NONE;
    std::optional<size_t> roomId;
    std::optional<size_t> crewMemberId;
};

#endif // !SELECTED_ENTITIES_MAP_HPP
