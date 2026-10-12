#include "skills_list_create_crew_member_model.hpp"
#include "q_variant_special_type.hpp"
#include "skill.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <qabstractitemmodel.h>
#include <qhashfunctions.h>
#include <qvariant.h>
#include <sstream>
#include <stdexcept>

int SkillsListCreateCrewMemberModel::columnCount(const QModelIndex &parent) const {
    return 3;
}

int SkillsListCreateCrewMemberModel::rowCount(const QModelIndex &parent) const {
    return this->skills.size();
}

QVariant SkillsListCreateCrewMemberModel::data(const QModelIndex &index, int role) const {
    std::optional<Skill> optionalSkill;

    try {
        optionalSkill = this->skills.at(index.row());
    } catch (std::out_of_range) {
        std::cout << "Warning in SkillsListCreateCrewMemberModel : skill list out of bound\n";
        return QVariant();
    }

    Skill skill = optionalSkill.value();

    switch (role) {
        case TypeRole: return util::QVariantSpecialType<SkillType>(skill.type);
        case NameRole: return QVariant(getSkillName(skill.type));
        case LevelRole: return util::qVariantSizeT(skill.level);
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> SkillsListCreateCrewMemberModel::roleNames() const {
    return {
        { TypeRole, "type"},
        { NameRole, "name"},
        { LevelRole, "level"},
    };
}

void SkillsListCreateCrewMemberModel::skillAddedCreateForm(SkillType skillType, QString level) {
    size_t levelNumber = -1;
    std::stringstream(level.toStdString()) >> levelNumber;

    Skill skill = {skillType, levelNumber};
    if (this->skills.contains(skill)) return;

    const int lastRowIndex = this->rowCount() - 1;
    const int lastColumnIndex = this->columnCount() - 1;

    this->layoutAboutToBeChanged();
    this->skills.push_back(skill);
    this->changePersistentIndex(this->index(0, 0), this->index(lastRowIndex, lastColumnIndex));
    this->layoutChanged();
}

void SkillsListCreateCrewMemberModel::skillRemovedCreateForm(SkillType skillType) {
    const int lastRowIndex = this->rowCount() - 1;
    const int lastColumnIndex = this->columnCount() - 1;

    this->layoutAboutToBeChanged();
    this->skills.removeIf([&skillType](const Skill &skill) -> bool { return skill.type == skillType; });
    this->changePersistentIndex(this->index(0, 0), this->index(lastRowIndex, lastColumnIndex));
    this->layoutChanged();
}
