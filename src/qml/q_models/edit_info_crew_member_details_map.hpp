#ifndef EDIT_INFO_CREW_MEMBER_DETAILS_MAP_HPP
#define EDIT_INFO_CREW_MEMBER_DETAILS_MAP_HPP

#include "crew_member_selected_event.hpp"
#include <QQmlPropertyMap>
#include <optional>
#include <cstddef>

class EditInfoCrewMemberDetailsMap : public QQmlPropertyMap, public CrewMemberSelectedSubscriber {
    Q_OBJECT
public:
    explicit EditInfoCrewMemberDetailsMap(QObject *parent = nullptr);

    void handleCrewMemberSelected(size_t &crewMemberId) override;

    void triggerSubscriptions();

public slots:
    void save(QString name, QString title, std::optional<size_t> currentRoom);
    void cancel();
    void openEditMenu();

private:
    std::optional<size_t> crewMemberId;

    void resetToCurrentValues();
};

#endif // !EDIT_INFO_CREW_MEMBER_DETAILS_MAP_HPP
