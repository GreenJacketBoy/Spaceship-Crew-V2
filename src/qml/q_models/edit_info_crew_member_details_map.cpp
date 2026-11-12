#include "selected_crew_member_id.hpp"
#include "edit_info_crew_member_details_map.hpp"
#include "crew_member.hpp"
#include "crew_member_moved_event.hpp"
#include "crew_member_name_updated_event.hpp"
#include "get_crew_list.hpp"
#include "get_crew_member.hpp"
#include "q_variant_special_type.hpp"
#include "game_state.hpp"
#include <cstddef>
#include <optional>
#include <qobject.h>
#include <qvariant.h>
#include <string>

EditInfoCrewMemberDetailsMap::EditInfoCrewMemberDetailsMap(QObject *parent) : QQmlPropertyMap(this, parent) {
    insert("id",          QString());
    insert("name",        QString());
    insert("title",       QString());
    insert("isEditing",   QVariant(false));
    insert("currentRoom", util::QVariantSpecialType(std::optional<size_t>()));
}

void EditInfoCrewMemberDetailsMap::handleCrewMemberSelected(size_t &crewMemberId) {
    this->resetToCurrentValues();
}

void EditInfoCrewMemberDetailsMap::resetToCurrentValues() {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    std::optional<CrewMember *> optionalCrewMember;
    if (!selectedCrewMemberId || !(optionalCrewMember = util::getCrewMember(selectedCrewMemberId.value()))) {
        insert("id",          QString());
        insert("name",        QString());
        insert("title",       QString());
        insert("currentRoom", util::QVariantSpecialType(std::optional<size_t>()));
        return;
    }

    auto crewMember = optionalCrewMember.value();

    insert("id", util::qVariantSizeT(crewMember->getId()));
    // First setting to garbage values before actually setting them, because if:
    // - UI changes the value
    // - Cancel is clicked
    // - The map still has the old values, which are different from the ones on the UI (there's no 2way binding)
    // - The old values are re-inserted, but because they are the same, the changes are not propagated to the UI
    // So setting it to another value before forces propagation to the UI
    insert("name", QString());
    insert("name", QVariant(QString::fromStdString(crewMember->getName())));
    insert("title", QString());
    insert("title", QVariant(QString::fromStdString(crewMember->getTitle())));
    insert("currentRoom", util::QVariantSpecialType(std::optional<size_t>()));
    insert("currentRoom", util::QVariantSpecialType(crewMember->getCurrentRoomId()));
}

void EditInfoCrewMemberDetailsMap::save(QString name, QString title, std::optional<size_t> currentRoom) {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    if (!selectedCrewMemberId) return;
    auto optionalCrewMember = util::getCrewMember(selectedCrewMemberId.value());
    if (!optionalCrewMember) return;
    auto crewMember = optionalCrewMember.value();

    std::string nameString = name.toStdString();
    std::string titleString = title.toStdString();
    if (nameString != crewMember->getName()) {
        CrewMemberNameUpdatedPayload payload = {crewMember->getId(), nameString.c_str()};
        GameState::getInstance().getEventManager()->getCrewMemberNameUpdatedEvent().emitEvent(payload);
    }
    if (titleString != crewMember->getTitle()) {
        CrewMemberTitleUpdatedPayload payload = {crewMember->getId(), titleString.c_str()};
        GameState::getInstance().getEventManager()->getCrewMemberTitleUpdatedEvent().emitEvent(payload);
    }
    if (currentRoom != crewMember->getCurrentRoomId()) {
        CrewMemberMovedPayload payload = {
            crewMember->getId(),
            crewMember->getCurrentRoomId(),
            currentRoom,
        };
        GameState::getInstance().getEventManager()->getCrewMemberMovedEvent().emitEvent(payload);
    }
    this->resetToCurrentValues();
    insert("isEditing", QVariant(false));
}

void EditInfoCrewMemberDetailsMap::cancel() {
    this->resetToCurrentValues();
    insert("isEditing", QVariant(false));
}

void EditInfoCrewMemberDetailsMap::openEditMenu() {
    this->resetToCurrentValues();
    insert("isEditing", QVariant(true));
}

void EditInfoCrewMemberDetailsMap::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
}
