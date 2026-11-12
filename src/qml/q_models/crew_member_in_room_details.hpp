#ifndef CREW_MEMBER_IN_ROOM_DETAILS_HPP
#define CREW_MEMBER_IN_ROOM_DETAILS_HPP

#include <cstddef>
#include "crew_member_deleted_event.hpp"
#include "crew_member_name_updated_event.hpp"
#include "crew_member_title_updated_event.hpp"
#include "crew_member_moved_event.hpp"
#include "room_selected_event.hpp"
#include <QAbstractTableModel>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class CrewMemberInRoomDetailsModel : public QAbstractTableModel, public CrewMemberMovedSubscriber, public RoomSelectedSubscriber, public CrewMemberNameUpdatedSubscriber, public CrewMemberTitleUpdatedSubscriber, public CrewMemberDeletedSubscriber {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleCrewMemberMoved(CrewMemberMovedPayload &crewMemberId) override;

    void handleRoomSelected(size_t &roomId) override;

    void handleCrewMemberTitleUpdated(CrewMemberTitleUpdatedPayload &payload) override;

    void handleCrewMemberNameUpdated(CrewMemberNameUpdatedPayload &payload) override;

    void handleCrewMemberDeleted(CrewMemberDeletedPayload &payload) override;


    void triggerSubscriptions();

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TitleRole,
    };
};

#endif // !CREW_MEMBER_IN_ROOM_DETAILS_HPP
