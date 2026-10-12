#ifndef ADD_SKILL_MODEL_HPP
#define ADD_SKILL_MODEL_HPP

#include <QAbstractTableModel>
#include <qabstractitemmodel.h>
#include <qhashfunctions.h>
#include <qnamespace.h>

class AddSkillModel : public QAbstractListModel {
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    enum ModelRoles {
        Text = Qt::UserRole + 1,
        Value,
    };
};

#endif // !ADD_SKILL_MODEL_HPP
