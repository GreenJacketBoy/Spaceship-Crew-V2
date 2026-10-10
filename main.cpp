#include "game_state.hpp"
#include "crew_member.hpp"
#include "room.hpp"
#include "room_type.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractListModel>
#include <memory>
#include <qobject.h>
#include <qqmlcontext.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto room1 = std::unique_ptr<Room>(new Room( "Mega Room 1 yolo yolo yolo yolo yolo", 1, 1, 1, RoomTypeEnum::QUARTER, {}));
    auto room2 = std::unique_ptr<Room>(new Room( "Mega Room 2 yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo yolo", 1, 1, 1, RoomTypeEnum::QUARTER, {}));
    auto room3 = std::unique_ptr<Room>(new Room( "Mega Room 3", 1, 1, 1, RoomTypeEnum::QUARTER, {}));
    auto room4 = std::unique_ptr<Room>(new Room( "Mega Room 4", 1, 1, 1, RoomTypeEnum::QUARTER, {}));
    auto room5 = std::unique_ptr<Room>(new Room( "Mega Room 5", 1, 1, 1, RoomTypeEnum::QUARTER, {}));
    std::map<size_t, std::unique_ptr<Room>> idToRoom_map;
    idToRoom_map.insert({room1->getId(), std::move(room1)});
    idToRoom_map.insert({room2->getId(), std::move(room2)});
    idToRoom_map.insert({room3->getId(), std::move(room3)});
    idToRoom_map.insert({room4->getId(), std::move(room4)});
    idToRoom_map.insert({room5->getId(), std::move(room5)});

    auto crew1 = std::unique_ptr<CrewMember>(new CrewMember( "James", "Pilot", {}));
    std::map<size_t, std::unique_ptr<CrewMember>> idToCrewMember_map;
    idToCrewMember_map.insert({crew1->getId(), std::move(crew1)});

    GameState *gameState = &GameState::getInstance();

    gameState->triggerSubscriptions();

    gameState->getSpaceShip().get()->value().getRoomMap().swap(idToRoom_map);
    gameState->getSpaceShip().get()->value().getCrewMap().swap(idToCrewMember_map);

    engine.rootContext()->setContextProperty("roomListModel", gameState->getRoomListModel().get());
    engine.rootContext()->setContextProperty("crewListModel", gameState->getCrewListModel().get());
    engine.rootContext()->setContextProperty("roomTypeModel", gameState->getRoomTypeModel().get());
    engine.rootContext()->setContextProperty("addAdjacentRoomModel", gameState->getAddAdjacentRoomModel().get());
    engine.rootContext()->setContextProperty("adjacentRoomsListCreateRoomModel", gameState->getAdjacentRoomsListCreateRoomModel().get());
    engine.rootContext()->setContextProperty("createRoomEvent", &gameState->getEventManager().get()->getCreateRoomEvent());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
