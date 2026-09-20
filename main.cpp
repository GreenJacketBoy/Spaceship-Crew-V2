#include "quarter.hpp"
#include "room.hpp"
#include "room_list_model.hpp"
#include "space_ship.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractListModel>
#include <algorithm>
#include <memory>
#include <qqmlcontext.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto room1 = std::unique_ptr<Room>(new Room( "Mega Room 1", 1, 1, 1, std::make_unique<Quarter>(), {}));
    auto room2 = std::unique_ptr<Room>(new Room( "Mega Room 2", 1, 1, 1, std::make_unique<Quarter>(), {}));
    auto room3 = std::unique_ptr<Room>(new Room( "Mega Room 3", 1, 1, 1, std::make_unique<Quarter>(), {}));
    auto room4 = std::unique_ptr<Room>(new Room( "Mega Room 4", 1, 1, 1, std::make_unique<Quarter>(), {}));
    auto room5 = std::unique_ptr<Room>(new Room( "Mega Room 5", 1, 1, 1, std::make_unique<Quarter>(), {}));
    std::map<size_t, std::unique_ptr<Room>> idToRoom_map;
    idToRoom_map.insert({room1->getId(), std::move(room1)});
    idToRoom_map.insert({room2->getId(), std::move(room2)});
    idToRoom_map.insert({room3->getId(), std::move(room3)});
    idToRoom_map.insert({room4->getId(), std::move(room4)});
    idToRoom_map.insert({room5->getId(), std::move(room5)});

    SpaceShip spaceShip = SpaceShip("yolo", "yolo", {}, std::move(idToRoom_map));
    
    engine.rootContext()->setContextProperty("roomListModel", &spaceShip.getRoomListModel());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
