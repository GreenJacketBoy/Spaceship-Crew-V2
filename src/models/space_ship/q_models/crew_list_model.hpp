#ifndef CREW_LIST_MODEL_HPP
#define CREW_LIST_MODEL_HPP

#include "crew_member_deleted_event.hpp"
#include "crew_member_name_updated_event.hpp"
#include "crew_member_title_updated_event.hpp"
#include "create_crew_member_event.hpp"
#include "crew_member_selected_event.hpp"
#include <QAbstractTableModel>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class CrewListModel : public QAbstractTableModel, public CreateCrewMemberSubscriber, public CrewMemberSelectedSubscriber, public CrewMemberNameUpdatedSubscriber, public CrewMemberTitleUpdatedSubscriber, public CrewMemberDeletedSubscriber {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleCrewMemberCreated(size_t &payload) override;

    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) override;

    void handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) override;

    void handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) override;

    void triggerSubscriptions();

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TitleRole,
        IsSelectedRole,
    };

    std::optional<size_t> selectedCrewMemberId;
};

#endif // !CREW_LIST_MODEL_HPP
