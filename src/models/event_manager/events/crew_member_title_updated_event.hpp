#ifndef CREW_MEMBER_TITLE_UPDATED_EVENT_HPP
#define CREW_MEMBER_TITLE_UPDATED_EVENT_HPP

#include "event_template.hpp"

struct CrewMemberTitleUpdatedPayload {
    const size_t crewMemberId;
    const char *title;
};

class CrewMemberTitleUpdatedSubscriber {
public: 
    virtual void handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) = 0;
};

class CrewMemberTitleUpdatedEvent : public Event<CrewMemberTitleUpdatedPayload, CrewMemberTitleUpdatedSubscriber> {
public:
    void emitEvent(CrewMemberTitleUpdatedPayload &payload) override;
};

#endif // !CREW_MEMBER_TITLE_UPDATED_EVENT_HPP
