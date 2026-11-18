#ifndef CREW_MEMBER_DETAILS_ADD_SKILL_MAP_HPP
#define CREW_MEMBER_DETAILS_ADD_SKILL_MAP_HPP

#include "crew_member_selected_event.hpp"
#include "crew_member_unselected_event.hpp"
#include "skill.hpp"
#include <QQmlPropertyMap>
#include <cstddef>

class CrewMemberDetailsAddSkillMap : public QQmlPropertyMap, public CrewMemberSelectedSubscriber, public CrewMemberUnselectedSubscriber {
    Q_OBJECT
public:
    explicit CrewMemberDetailsAddSkillMap(QObject *parent = nullptr);

    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void handleCrewMemberUnselected(size_t &crewMemberId) override;

    void triggerSubscriptions();

public slots:
    void edit();
    void save(SkillType skillType, QString levelString);
    void cancel();

};

#endif // !CREW_MEMBER_DETAILS_ADD_SKILL_MAP_HPP
