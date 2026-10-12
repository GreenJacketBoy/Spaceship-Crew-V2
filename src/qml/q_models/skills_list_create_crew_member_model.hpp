#ifndef SKILLS_LIST_CREATE_CREW_MEMBER_MODEL_HPP
#define SKILLS_LIST_CREATE_CREW_MEMBER_MODEL_HPP

#include "skill.hpp"
#include <QAbstractTableModel>
#include <qhashfunctions.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <qvariant.h>

class SkillsListCreateCrewMemberModel : public QAbstractTableModel {
Q_OBJECT
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QList<Skill> *getSkills() { return &this->skills; };

public slots: 
    void skillAddedCreateForm(SkillType skillType, QString level);
    void skillRemovedCreateForm(SkillType skillType);

private:
    enum ModelRoles {
        TypeRole = Qt::UserRole + 1,
        NameRole,
        LevelRole,
    };

    QList<Skill> skills;
};

#endif // !SKILLS_LIST_CREATE_CREW_MEMBER_MODEL_HPP
