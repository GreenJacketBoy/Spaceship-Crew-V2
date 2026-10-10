#include "crew_member.hpp"
#include "crew_list_model.hpp"
#include "get_crew_list.hpp"
#include "q_variant_special_type.hpp"

int CrewListModel::columnCount(const QModelIndex &parent) const {
    auto crewList = util::getCrewList();
    if (!crewList) return 0;
    return 1;
}

int CrewListModel::rowCount(const QModelIndex &parent) const {
    auto crewList = util::getCrewList();
    if (!crewList) return 0;
    return crewList.value()->size();
}

QVariant CrewListModel::data(const QModelIndex &index, int role) const {
    auto crewList = util::getCrewList();
    if (!crewList) return QVariant();
    size_t i = 0;
    for (auto &[_, crewMember] : *crewList.value()) {
        if (index.row() == i) {
            switch (role) {
                case IdRole: return util::qVariantSizeT(crewMember->getId());
                case NameRole: return QVariant(crewMember->getName().c_str());
                case TitleRole: return QVariant(crewMember->getTitle().c_str());
                default: return QVariant();
            }
        }
        i++;
    }
    return QVariant();
}

QHash<int, QByteArray> CrewListModel::roleNames() const {
    return {
        { IdRole, "id"},
        { NameRole, "name"},
        { TitleRole, "title"},
    };
}
