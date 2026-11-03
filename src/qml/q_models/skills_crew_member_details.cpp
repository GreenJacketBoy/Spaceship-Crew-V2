#include "skills_crew_member_details.hpp"
#include "get_crew_member.hpp"
#include "q_variant_special_type.hpp"
#include "at_index.hpp"
#include "game_state.hpp"
#include "skill.hpp"
#include <cstddef>
#include <optional>
#include <qdebug.h>
#include <qvariant.h>

int SkillsCrewMemberDetailsModel::rowCount(const QModelIndex &parent) const {
    if (!this->crewMemberId) return 0;
    auto optionalCrewMember = util::getCrewMember(this->crewMemberId.value());
    if (!optionalCrewMember) return 0;
    auto crewMember = optionalCrewMember.value();

    return crewMember->getSkills().size();
}

QVariant SkillsCrewMemberDetailsModel::data(const QModelIndex &index, int role) const {
    if (!this->crewMemberId) return QVariant();
    auto optionalCrewMember = util::getCrewMember(this->crewMemberId.value());
    if (!optionalCrewMember) return QVariant();
    auto crewMember = optionalCrewMember.value();
    auto optionalSkillType = util::atIndexKey(crewMember->getSkills(), index.row());
    if (!optionalSkillType) return QVariant();

    SkillType skillType = *optionalSkillType.value();
    size_t level = crewMember->getSkillLevel(skillType);

    switch (role) {
        case NameRole: return QVariant(getSkillName(skillType));
        case LevelRole: return util::qVariantSizeT(level);
        default: return QVariant();
    }
    return QVariant();
}

void SkillsCrewMemberDetailsModel::handleCrewMemberSelected(size_t &crewMemberId) {
    this->layoutAboutToBeChanged();
    this->crewMemberId = crewMemberId;
    this->changePersistentIndex(this->index(0, 0), this->index(this->rowCount(), 0));
    this->layoutChanged();
}

QHash<int, QByteArray> SkillsCrewMemberDetailsModel::roleNames() const {
    return {
        { NameRole, "name"},
        { LevelRole, "level"},
    };
}

void SkillsCrewMemberDetailsModel::triggerSubscriptions() {
    GameState::getInstance().getEventManager()->getCrewMemberSelectedEvent().subscribe(*this);
}
