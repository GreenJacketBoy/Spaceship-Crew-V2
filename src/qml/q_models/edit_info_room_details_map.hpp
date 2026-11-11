#ifndef EDIT_INFO_ROOM_DETAILS_MAP_HPP
#define EDIT_INFO_ROOM_DETAILS_MAP_HPP

#include "room_selected_event.hpp"
#include "room_type.hpp"
#include <QQmlPropertyMap>
#include <optional>
#include <cstddef>
#include <qobject.h>

class EditInfoRoomDetailsMap : public QQmlPropertyMap, public RoomSelectedSubscriber {
    Q_OBJECT
public:
    explicit EditInfoRoomDetailsMap(QObject *parent = nullptr);

    void handleRoomSelected(size_t &crewMemberId) override;

    void triggerSubscriptions();

public slots:
    void save(QString name, QString crewCapacityAsString, QString storageCapacityAsString, QString sizeAsString, RoomTypeEnum roomType);
    void cancel();
    void openEditMenu();

private:
    std::optional<size_t> roomId;

    void resetToCurrentValues();
};

#endif // !EDIT_INFO_ROOM_DETAILS_MAP_HPP
