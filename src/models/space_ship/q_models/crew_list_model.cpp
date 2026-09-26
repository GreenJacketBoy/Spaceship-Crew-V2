#include "crew_list_model.hpp"
#include "q_variant_size_t.hpp"

int CrewListModel::columnCount(const QModelIndex &parent) const {
    if (!this->crewList) return 0;
    return 1;
}

int CrewListModel::rowCount(const QModelIndex &parent) const {
    if (!this->crewList) return 0;
    return this->crewList.value()->size();
}

QVariant CrewListModel::data(const QModelIndex &index, int role) const {
    if (!this->crewList.has_value()) return QVariant();
    size_t i = 0;
    for (auto &[_, room] : *this->crewList.value()) {
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

void CrewListModel::setCrewList(std::map<size_t, std::unique_ptr<CrewMember>> &crewList) {
    this->crewList = &crewList;
}
