#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "skills_crew_member_details.hpp"
#include "next_immediate_rooms_crew_member_details.hpp"
#include "selected_entities_map.hpp"
#include "adjacent_room_list_room_details.hpp"
#include "add_adjacent_room_model.hpp"
#include "add_skill_model.hpp"
#include "adjacent_rooms_list_create_room.hpp"
#include "current_room_model.hpp"
#include "event_manager.hpp"
#include "crew_list_model.hpp"
#include "info_room_details_map.hpp"
#include "room_list_model.hpp"
#include "room_type_model.hpp"
#include "skills_list_create_crew_member_model.hpp"
#include "space_ship.hpp"
#include "crew_member_in_room_details.hpp"
#include <memory>
#include <optional>

class GameState {
public: 
    static inline GameState &getInstance() {
        static GameState instance;
        return instance;
    };

    inline auto &getSpaceShip() { return this->spaceShip; } // TEMPORARY ?
    inline auto &getRoomListModel() { return this->roomListModel; }
    inline auto &getCrewListModel() { return this->crewListModel; }
    inline auto &getRoomTypeModel() { return this->roomTypeModel; }
    inline auto &getAddAdjacentRoomModel() { return this->addAdjacentRoomModel; }
    inline auto &getAdjacentRoomsListCreateRoomModel() { return this->adjacentRoomsListCreateRoomModel; }
    inline auto &getAddSkillModel() { return this->addSkillModel; }
    inline auto &getSkillsListCreateCrewMemberModel() { return this->skillsListCreateCrewMemberModel; }
    inline auto &getEventManager() { return this->eventManager; }
    inline auto &getAdjacentRoomListRoomDetailsModel() { return this->adjacentRoomListRoomDetailsModel; }
    inline auto &getCurrentRoomModel() { return this->currentRoomModel; }
    inline auto &getCrewMemberInRoomDetailsModel() { return this->crewMemberInRoomDetailsModel; }
    inline auto &getInfoRoomDetailsMap() { return this->infoRoomDetailsMap; }
    inline auto &getSelectedEntitiesMap() { return this->selectedEntitiesMap; }
    inline auto &getNextImmediateRoomsCrewMemberDetailsModel() { return this->nextImmediateRoomsCrewMemberDetailsModel; }
    inline auto &getSkillsCrewMemberDetailsModel() { return this->skillsCrewMemberDetailsModel; }

    void triggerSubscriptions();

private:
    GameState() {};
    // TEMPORARY
    std::unique_ptr<std::optional<SpaceShip>> spaceShip = std::unique_ptr<std::optional<SpaceShip>>(new std::optional<SpaceShip>(SpaceShip("Antarctica", "Fr", {}, {})));

    std::unique_ptr<EventManager>  eventManager = std::make_unique<EventManager>();
    std::unique_ptr<RoomTypeModel> roomTypeModel = std::make_unique<RoomTypeModel>();
    std::unique_ptr<RoomListModel> roomListModel = std::make_unique<RoomListModel>();
    std::unique_ptr<CrewListModel> crewListModel = std::make_unique<CrewListModel>();
    std::unique_ptr<AddAdjacentRoomModel> addAdjacentRoomModel = std::make_unique<AddAdjacentRoomModel>();
    std::unique_ptr<AdjacentRoomsListCreateRoomModel> adjacentRoomsListCreateRoomModel = std::make_unique<AdjacentRoomsListCreateRoomModel>();
    std::unique_ptr<AddSkillModel> addSkillModel = std::make_unique<AddSkillModel>();
    std::unique_ptr<SkillsListCreateCrewMemberModel> skillsListCreateCrewMemberModel = std::make_unique<SkillsListCreateCrewMemberModel>();
    std::unique_ptr<AdjacentRoomListRoomDetailsModel> adjacentRoomListRoomDetailsModel = std::make_unique<AdjacentRoomListRoomDetailsModel>();
    std::unique_ptr<CurrentRoomModel> currentRoomModel = std::make_unique<CurrentRoomModel>();
    std::unique_ptr<CrewMemberInRoomDetailsModel> crewMemberInRoomDetailsModel = std::make_unique<CrewMemberInRoomDetailsModel>();
    std::unique_ptr<InfoRoomDetailsMap> infoRoomDetailsMap = std::make_unique<InfoRoomDetailsMap>();
    std::unique_ptr<SelectedEntitiesMap> selectedEntitiesMap = std::make_unique<SelectedEntitiesMap>();
    std::unique_ptr<NextImmediateRoomsCrewMemberDetailsModel> nextImmediateRoomsCrewMemberDetailsModel = std::make_unique<NextImmediateRoomsCrewMemberDetailsModel>();
    std::unique_ptr<SkillsCrewMemberDetailsModel> skillsCrewMemberDetailsModel = std::make_unique<SkillsCrewMemberDetailsModel>();
};

#endif // !GAME_STATE_HPP