#ifndef CREW_MEMBER_NAME_UPDATED_EVENT_HPP
#define CREW_MEMBER_NAME_UPDATED_EVENT_HPP

#include "event_template.hpp"

struct CrewMemberNameUpdatedPayload {
    const size_t crewMemberId;
    const char *name;
};

class CrewMemberNameUpdatedSubscriber {
public: 
    virtual void handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) = 0;
};

class CrewMemberNameUpdatedEvent : public Event<CrewMemberNameUpdatedPayload, CrewMemberNameUpdatedSubscriber> {
public:
    void emitEvent(CrewMemberNameUpdatedPayload &payload) override;
};

#endif // !CREW_MEMBER_NAME_UPDATED_EVENT_HPP
