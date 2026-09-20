#ifndef CREW_LIST_MODEL_HPP
#define CREW_LIST_MODEL_HPP

#include <cstddef>
#include <optional>
#include "crew_member.hpp"
#include <QAbstractTableModel>
#include <qhashfunctions.h>
#include <qnamespace.h>
#include <qvariant.h>

class CrewListModel : public QAbstractTableModel {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setCrewList(std::map<size_t, std::unique_ptr<CrewMember>> &roomList);

private:
    enum RoomModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TitleRole,
    };

    std::optional<std::map<size_t, std::unique_ptr<CrewMember>>*> crewList;
};

#endif // !CREW_LIST_MODEL_HPP
