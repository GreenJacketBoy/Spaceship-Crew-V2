#include "add_skill_model.hpp"
#include "q_variant_special_type.hpp"
#include "skill.hpp"
#include <iostream>
#include <qvariant.h>

int AddSkillModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

int AddSkillModel::rowCount(const QModelIndex &parent) const {
    return AMOUNT_OF_SKILLS;
}

QVariant AddSkillModel::data(const QModelIndex &index, int role) const {
    if (index.row() > AMOUNT_OF_SKILLS - 1) {
        std::cout << "Warning in AddSkillModel, requested row's index is higher than there are Skill Types (row " << index.row() << " but " << AMOUNT_OF_SKILLS << " types)\n";
        return QVariant();
    }
    SkillType skillType = static_cast<SkillType>(index.row());

    switch (role) {
        case Text: return QVariant(getSkillName(skillType));
        case Value: return util::QVariantSpecialType<SkillType>(skillType);
    }

    return QVariant();
}

QHash<int, QByteArray> AddSkillModel::roleNames() const {
    return {
        { Text, "text"},
        { Value, "value"},
    };
}
