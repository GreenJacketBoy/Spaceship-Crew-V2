#ifndef SKILLS_CREW_MEMBER_DETAILS_HPP
#define SKILLS_CREW_MEMBER_DETAILS_HPP

#include "crew_member_selected_event.hpp"
#include <cstddef>
#include <QAbstractListModel>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class SkillsCrewMemberDetailsModel : public QAbstractListModel, public CrewMemberSelectedSubscriber {
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void triggerSubscriptions();

private:
    enum ModelRoles {
        NameRole = Qt::UserRole + 1,
        LevelRole,
    };

    std::optional<size_t> crewMemberId;
};

#endif // !SKILLS_CREW_MEMBER_DETAILS_HPP
