#ifndef SKILLS_CREW_MEMBER_DETAILS_HPP
#define SKILLS_CREW_MEMBER_DETAILS_HPP

#include "crew_member_selected_event.hpp"
#include "crew_member_skill_updated_event.hpp"
#include "skill.hpp"
#include <array>
#include <cstddef>
#include <QAbstractListModel>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <qvariant.h>

class SkillsCrewMemberDetailsModel : public QAbstractListModel, public CrewMemberSelectedSubscriber, public CrewMemberSkillUpdatedSubscriber {
Q_OBJECT
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void handleCrewMemberSkillUpdated(CrewMemberSkillUpdatedPayload &payload) override;

    void triggerSubscriptions();

public slots:
    void edit(SkillType skillType);
    void save(SkillType skillType, QString levelString);
    void cancel(SkillType skillType);

private:
    enum ModelRoles {
        NameRole = Qt::UserRole + 1,
        LevelRole,
        IsEditingRole,
        TypeRole,
    };
    std::array<bool, AMOUNT_OF_SKILLS> skillsEditStatus = {}; // initialized as 0 (false)
    constexpr void setIsEditing(SkillType skillType, bool isEditing);
};

#endif // !SKILLS_CREW_MEMBER_DETAILS_HPP
