#include "skills_crew_member_details.hpp"
#include "crew_member.hpp"
#include "crew_member_skill_updated_event.hpp"
#include "get_crew_member.hpp"
#include "index_of.hpp"
#include "q_variant_special_type.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include "selected_crew_member_id.hpp"
#include "skill.hpp"
#include <cstddef>
#include <optional>
#include <qvariant.h>

int SkillsCrewMemberDetailsModel::rowCount(const QModelIndex &parent) const {
    auto optionalCrewMember = util::getCrewMember(util::selectedCrewMemberId());
    if (!optionalCrewMember) return 0;
    auto crewMember = optionalCrewMember.value();

    return crewMember->getSkills().size();
}

QVariant SkillsCrewMemberDetailsModel::data(const QModelIndex &index, int role) const {
    auto optionalCrewMember = util::getCrewMember(util::selectedCrewMemberId());
    if (!optionalCrewMember) return QVariant();
    auto crewMember = optionalCrewMember.value();
    auto optionalSkillType = util::atIndexKey(crewMember->getSkills(), index.row());
    if (!optionalSkillType) return QVariant();

    SkillType skillType = *optionalSkillType.value();
    size_t level = crewMember->getSkillLevel(skillType);

    switch (role) {
        case NameRole: return QVariant(getSkillName(skillType));
        case LevelRole: return util::qVariantSizeT(level);
        case IsEditingRole: return QVariant(skillsEditStatus.at(static_cast<size_t>(skillType)));
        case TypeRole: return util::qVariantSizeT(static_cast<size_t>(skillType));
        default: return QVariant();
    }
    return QVariant();
}

void SkillsCrewMemberDetailsModel::handleCrewMemberSelected(size_t &crewMemberId) {
    for (bool &status : this->skillsEditStatus) {
        status = false;
    }
    this->layoutAboutToBeChanged();
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
    this->layoutChanged();
}

void SkillsCrewMemberDetailsModel::handleCrewMemberSkillUpdated(CrewMemberSkillUpdatedPayload &payload) {
    const auto selectedCrewMemberId = util::selectedCrewMemberId();
    if (!selectedCrewMemberId) return;
    if (selectedCrewMemberId.value() != payload.crewMemberId) return;

    auto optionalCrewMember = util::getCrewMember(payload.crewMemberId);
    if (!optionalCrewMember) return;

    bool wasRemoved = payload.newLevel == 0;
    bool wasFirstAdded = payload.previousLevel == 0;
    if (wasRemoved || wasFirstAdded) {
        this->layoutAboutToBeChanged();
        this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount()-1, 0));
        this->layoutChanged();
        return;
    }

    auto optionalIndex = util::indexOf<size_t>(optionalCrewMember.value()->getSkills(), payload.skillType);
    if (!optionalIndex) return;
    const size_t index = optionalIndex.value();

    dataChanged(this->index(index, 0), this->index(index, 0));
}

QHash<int, QByteArray> SkillsCrewMemberDetailsModel::roleNames() const {
    return {
        { NameRole, "name"},
        { LevelRole, "level"},
        { IsEditingRole, "isEditing"},
        { TypeRole, "type"},
    };
}

constexpr void SkillsCrewMemberDetailsModel::setIsEditing(SkillType skillType, bool isEditing) {
    this->skillsEditStatus.at(static_cast<size_t>(skillType)) = isEditing;

    auto optionalCrewMember = util::getCrewMember(util::selectedCrewMemberId());
    if (!optionalCrewMember) return;

    auto optionalIndex = util::indexOf<size_t>(optionalCrewMember.value()->getSkills(), skillType);
    if (!optionalIndex) return;
    const size_t index = optionalIndex.value();

    this->dataChanged(this->index(index, 0), this->index(index, 0));
}

void SkillsCrewMemberDetailsModel::edit(SkillType skillType) {
    this->setIsEditing(skillType, true);
}

void SkillsCrewMemberDetailsModel::cancel(SkillType skillType) {
    this->setIsEditing(skillType, false);
}

void SkillsCrewMemberDetailsModel::save(SkillType skillType, QString levelString) {
    auto optionalCrewMember = util::getCrewMember(util::selectedCrewMemberId());
    if (!optionalCrewMember) return;
    CrewMember *crewMember = optionalCrewMember.value();

    size_t level = -1;
    auto stream = std::stringstream(levelString.toStdString());
    stream >> level;

    this->skillsEditStatus.at(static_cast<size_t>(skillType)) = false;
    CrewMemberSkillUpdatedPayload payload = {
        crewMember->getId(),
        skillType, 
        level,
        crewMember->getSkillLevel(skillType),
    };
    GameState::getInstance().getEventManager()->getCrewMemberSkillUpdatedEvent().emitEvent(payload);
}

void SkillsCrewMemberDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
    GameState::getInstance().getEventManager()->getCrewMemberSkillUpdatedEvent().subscribe(*this);
}
