#ifndef CREATE_CREW_MEMBER_EVENT_HPP
#define CREATE_CREW_MEMBER_EVENT_HPP

#include "event_template.hpp"
#include <cstddef>
#include <qlist.h>
#include <qobject.h>
#include <qtmetamacros.h>

class CrewMember;
struct Skill;

class CreateCrewMemberSubscriber {
public: 
    virtual void handleCrewMemberCreated(size_t &payload) = 0;
};

class CreateCrewMemberEvent : public QObject, public Event<size_t, CreateCrewMemberSubscriber> {
    Q_OBJECT
public:
    void emitEvent(size_t &crewMemberId) override;

public slots:
    void createCrewMember(
        QString name,
        QString title,
        std::optional<size_t> optionalCurrentRoomId,
        QList<Skill> *skills
    );
};

#endif // !CREATE_CREW_MEMBER_EVENT_HPP
