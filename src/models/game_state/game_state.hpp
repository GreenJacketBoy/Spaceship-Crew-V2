#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "event_manager.hpp"
#include "crew_list_model.hpp"
#include "room_list_model.hpp"
#include "room_type_model.hpp"
#include "space_ship.hpp"
#include <memory>
#include <optional>

class GameState {
public: 
    static inline GameState &getInstance() {
        static GameState instance;
        return instance;
    };

    inline auto &getSpaceShip() { return this->spaceShip; } // TEMPORARY
    inline auto &getRoomListModel() { return this->roomListModel; }
    inline auto &getCrewListModel() { return this->crewListModel; }
    inline auto &getRoomTypeModel() { return this->roomTypeModel; }
    inline auto &getEventManager() { return this->eventManager; }

    void triggerSubscriptions();

private:
    GameState() {};
    // TEMPORARY
    std::unique_ptr<std::optional<SpaceShip>> spaceShip = std::unique_ptr<std::optional<SpaceShip>>(new std::optional<SpaceShip>(SpaceShip("Antarctica", "Fr", {}, {})));

    std::unique_ptr<EventManager>  eventManager = std::make_unique<EventManager>();
    std::unique_ptr<RoomTypeModel> roomTypeModel = std::make_unique<RoomTypeModel>();
    std::unique_ptr<RoomListModel> roomListModel = std::make_unique<RoomListModel>();
    std::unique_ptr<CrewListModel> crewListModel = std::make_unique<CrewListModel>();
};

#endif // !GAME_STATE_HPP