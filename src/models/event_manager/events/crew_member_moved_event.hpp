#ifndef CREW_MEMBER_MOVED_EVENT_HPP
#define CREW_MEMBER_MOVED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qtmetamacros.h>

struct CrewMemberMovedPayload {
    size_t crewMemberId;
    std::optional<size_t> fromRoomId;
    std::optional<size_t> toRoomId;
};

class CrewMemberMovedSubscriber{
public: 
    virtual void handleCrewMemberMoved(CrewMemberMovedPayload &payload) = 0;
};

class CrewMemberMovedEvent : public Event<CrewMemberMovedPayload, CrewMemberMovedSubscriber> {
public:
    void emitEvent(CrewMemberMovedPayload &payload);
};

#endif // !CREW_MEMBER_MOVED_EVENT_HPP
