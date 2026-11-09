#ifndef INFO_CREW_MEMBER_DETAILS_MAP_HPP
#define INFO_CREW_MEMBER_DETAILS_MAP_HPP

#include "crew_member_name_updated_event.hpp"
#include "crew_member_title_updated_event.hpp"
#include "crew_member_moved_event.hpp"
#include "crew_member_selected_event.hpp"
#include <QQmlPropertyMap>
#include <optional>
#include <cstddef>

class InfoCrewMemberDetailsMap : public QQmlPropertyMap, public CrewMemberSelectedSubscriber, public CrewMemberMovedSubscriber, public CrewMemberNameUpdatedSubscriber, public CrewMemberTitleUpdatedSubscriber   {
    Q_OBJECT
public:
    explicit InfoCrewMemberDetailsMap(QObject *parent = nullptr);

    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void handleCrewMemberMoved(CrewMemberMovedPayload &payload) override;

    void handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) override;

    void handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) override;

    void triggerSubscriptions();

private:
    std::optional<size_t> crewMemberId;

    void updateCurrentRoom(const std::optional<size_t> &crewMemberId);
};

#endif // !INFO_CREW_MEMBER_DETAILS_MAP_HPP
