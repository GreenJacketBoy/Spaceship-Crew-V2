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
    for (auto &[_, room] : *crewList.value()) {
        if (index.row() == i) {
            switch (role) {
                case IdRole: return util::qVariantSizeT(room->getId());
                case NameRole: return QVariant(room->getName().c_str());
                case TitleRole: return QVariant(room->getTitle().c_str());
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
