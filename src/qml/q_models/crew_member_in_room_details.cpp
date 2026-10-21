#include "crew_member_in_room_details.hpp"
#include "get_crew_member.hpp"
#include "q_variant_special_type.hpp"
#include "get_room.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include <qvariant.h>

int CrewMemberInRoomDetailsModel::columnCount(const QModelIndex &parent) const {
    return 3;
}

int CrewMemberInRoomDetailsModel::rowCount(const QModelIndex &parent) const {
    if (!this->roomId) return 0;
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return 0;
    return optionalRoom.value()->getCrewMembersInRoom().size();
}

QVariant CrewMemberInRoomDetailsModel::data(const QModelIndex &index, int role) const {
    if (!this->roomId) return QVariant();
    auto optionalRoom = util::getRoom(this->roomId.value());
    if (!optionalRoom) return QVariant();
    auto &crewMembersInRoom = optionalRoom.value()->getCrewMembersInRoom();

    auto optionalCrewMemberIdAtIndex = util::atIndex(crewMembersInRoom, index.row());
    if (!optionalCrewMemberIdAtIndex) return QVariant();
    auto optionalCrewMemberAtIndex = util::getCrewMember(*optionalCrewMemberIdAtIndex.value());
    if (!optionalCrewMemberAtIndex) return QVariant();
    auto crewMember = optionalCrewMemberAtIndex.value();

    switch (role) {
        case IdRole: return util::qVariantSizeT(crewMember->getId());
        case NameRole: return QVariant(crewMember->getName().c_str());
        case TitleRole: return QVariant(crewMember->getTitle().c_str());
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> CrewMemberInRoomDetailsModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { TitleRole, "title"},
    };
}

void CrewMemberInRoomDetailsModel::handleCrewMemberCreated(size_t &crewMemberId) {
    if (!this->roomId) return;
    auto selectedRoomId = this->roomId.value();
    auto optionalSelectedRoom = util::getRoom(selectedRoomId);
    if (!optionalSelectedRoom) return;
    if (!optionalSelectedRoom.value()->getCrewMembersInRoom().contains(crewMemberId)) return;

    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void CrewMemberInRoomDetailsModel::handleRoomSelected(size_t &roomId) {
    auto optionalRoom = util::getRoom(roomId);
    if (!optionalRoom) return;

    this->layoutAboutToBeChanged();
    this->roomId = roomId;
    this->changePersistentIndex(this->index(0, this->columnCount()-1), this->index(this->rowCount()-1, this->columnCount()-1));
    this->layoutChanged();
}

void CrewMemberInRoomDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCreateCrewMemberEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getRoomSelectedEvent().subscribe(*this);
}
