#ifndef CREW_MEMBER_SELECTED_EVENT_HPP
#define CREW_MEMBER_SELECTED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <qobject.h>
#include <qtmetamacros.h>

class CrewMemberSelectedSubscriber {
public: 
    virtual void handleCrewMemberSelected(size_t &payload) = 0;
};

class CrewMemberSelectedEvent : public QObject, public Event<size_t, CrewMemberSelectedSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &crewMemberId) override;

public slots:
    inline void selectCrewMember(size_t crewMemberId) { this->emitEvent(crewMemberId); };
};

#endif // !CREW_MEMBER_SELECTED_EVENT_HPP
