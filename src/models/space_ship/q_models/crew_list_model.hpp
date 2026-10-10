#ifndef CREW_LIST_MODEL_HPP
#define CREW_LIST_MODEL_HPP

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

private:
    enum ModelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TitleRole,
    };
};

#endif // !CREW_LIST_MODEL_HPP
