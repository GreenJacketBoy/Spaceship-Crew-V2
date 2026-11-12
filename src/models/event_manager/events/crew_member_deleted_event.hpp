#ifndef CREW_MEMBER_DELETED_EVENT_HPP
#define CREW_MEMBER_DELETED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qtmetamacros.h>

struct CrewMemberDeletedPayload {
    const size_t deletedCrewMemberId;
    const std::optional<size_t> deletedCrewMemberCurrentRoomId;
};

class CrewMemberDeletedSubscriber {
public: 
    virtual void handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) = 0;
};

class CrewMemberDeletedEvent : public QObject, public Event<CrewMemberDeletedPayload, CrewMemberDeletedSubscriber> {
    Q_OBJECT
public:
    void emitEvent(CrewMemberDeletedPayload &payload) override;

public slots:
    void deleteCrewMember(size_t crewMemberId);
};

#endif // !CREW_MEMBER_DELETED_EVENT_HPP
