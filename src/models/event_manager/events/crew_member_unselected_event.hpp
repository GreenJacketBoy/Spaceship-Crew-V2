#ifndef CREW_MEMBER_UNSELECTED_EVENT_HPP
#define CREW_MEMBER_UNSELECTED_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <qobject.h>
#include <qtmetamacros.h>

class CrewMemberUnselectedSubscriber {
public: 
    virtual void handleCrewMemberUnselected(size_t &payload) = 0;
};

class CrewMemberUnselectedEvent : public QObject, public Event<size_t, CrewMemberUnselectedSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &crewMemberId) override;

public slots:
    inline void selectCrewMember(size_t crewMemberId) { this->emitEvent(crewMemberId); };
};

#endif // !CREW_MEMBER_UNSELECTED_EVENT_HPP
