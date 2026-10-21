#ifndef CREW_MEMBER_IN_ROOM_DETAILS_HPP
#define CREW_MEMBER_IN_ROOM_DETAILS_HPP

#include <cstddef>
#include "create_crew_member_event.hpp"
#include "room_selected_event.hpp"
#include <QAbstractTableModel>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class CrewMemberInRoomDetailsModel : public QAbstractTableModel, public CreateCrewMemberSubscriber, public RoomSelectedSubscriber {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleCrewMemberCreated(size_t &crewMemberId) override;

    void handleRoomSelected(size_t &roomId) override;

    void triggerSubscriptions();

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TitleRole,
    };

    std::optional<size_t> roomId;
};

#endif // !CREW_MEMBER_IN_ROOM_DETAILS_HPP
