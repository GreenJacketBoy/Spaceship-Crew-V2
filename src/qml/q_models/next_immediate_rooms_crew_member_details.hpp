#ifndef NEXT_IMMEDIATE_ROOMS_CREW_MEMBER_DETAILS_HPP
#define NEXT_IMMEDIATE_ROOMS_CREW_MEMBER_DETAILS_HPP

#include "create_room_event.hpp"
#include "crew_member_moved_event.hpp"
#include <cstddef>
#include <QAbstractListModel>
#include <optional>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class NextImmediateRoomsCrewMemberDetailsModel : public QAbstractListModel, public CreateRoomSubscriber, public CrewMemberMovedSubscriber {
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void handleRoomCreated(size_t &roomId) override;

    void handleCrewMemberMoved(CrewMemberMovedPayload &payload) override;

    void triggerSubscriptions();

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CrewCapacityRole,
        StorageCapacityRole,
        SizeRole,
        TypeRole,
    };

    constexpr std::optional<Room *> getCurrentRoom() const;

    std::optional<size_t> crewMemberId;
};

#endif // !NEXT_IMMEDIATE_ROOMS_CREW_MEMBER_DETAILS_HPP
