#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "crew_member_details_add_skill_map.hpp"
#include "edit_info_crew_member_details_map.hpp"
#include "edit_current_room_model.hpp"
#include "edit_info_room_details_map.hpp"
#include "edit_room_type_model.hpp"
#include "info_crew_member_details_map.hpp"
#include "room_details_edit_adjacent_rooms_map.hpp"
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
    inline auto &getInfoCrewMemberDetailsMap() { return this->infoCrewMemberDetailsMap; }
    inline auto &getEditInfoCrewMemberDetailsMap() { return this->editInfoCrewMemberDetailsMap; }
    inline auto &getEditCurrentRoomModel() { return this->editCurrentRoomModel; }
    inline auto &getEditInfoRoomDetailsMap() { return this->editInfoRoomDetailsMap; }
    inline auto &getEditRoomTypeModel() { return this->editRoomTypeModel; }
    inline auto &getCrewMemberDetailsAddSkillMap() { return this->crewMemberDetailsAddSkillMap; }
    inline auto &getRoomDetailsEditAdjacentRoomsMap() { return this->roomDetailsEditAdjacentRoomsMap; }

    void triggerSubscriptions();

private:
    GameState() {};
    // TEMPORARY
    const std::unique_ptr<std::optional<SpaceShip>> spaceShip = std::unique_ptr<std::optional<SpaceShip>>(new std::optional<SpaceShip>(SpaceShip("Antarctica", "Fr", {}, {})));

    const std::unique_ptr<EventManager>  eventManager = std::make_unique<EventManager>();
    const std::unique_ptr<RoomTypeModel> roomTypeModel = std::make_unique<RoomTypeModel>();
    const std::unique_ptr<RoomListModel> roomListModel = std::make_unique<RoomListModel>();
    const std::unique_ptr<CrewListModel> crewListModel = std::make_unique<CrewListModel>();
    const std::unique_ptr<AddAdjacentRoomModel> addAdjacentRoomModel = std::make_unique<AddAdjacentRoomModel>();
    const std::unique_ptr<AdjacentRoomsListCreateRoomModel> adjacentRoomsListCreateRoomModel = std::make_unique<AdjacentRoomsListCreateRoomModel>();
    const std::unique_ptr<AddSkillModel> addSkillModel = std::make_unique<AddSkillModel>();
    const std::unique_ptr<SkillsListCreateCrewMemberModel> skillsListCreateCrewMemberModel = std::make_unique<SkillsListCreateCrewMemberModel>();
    const std::unique_ptr<AdjacentRoomListRoomDetailsModel> adjacentRoomListRoomDetailsModel = std::make_unique<AdjacentRoomListRoomDetailsModel>();
    const std::unique_ptr<CurrentRoomModel> currentRoomModel = std::make_unique<CurrentRoomModel>();
    const std::unique_ptr<CrewMemberInRoomDetailsModel> crewMemberInRoomDetailsModel = std::make_unique<CrewMemberInRoomDetailsModel>();
    const std::unique_ptr<InfoRoomDetailsMap> infoRoomDetailsMap = std::make_unique<InfoRoomDetailsMap>();
    const std::unique_ptr<SelectedEntitiesMap> selectedEntitiesMap = std::make_unique<SelectedEntitiesMap>();
    const std::unique_ptr<NextImmediateRoomsCrewMemberDetailsModel> nextImmediateRoomsCrewMemberDetailsModel = std::make_unique<NextImmediateRoomsCrewMemberDetailsModel>();
    const std::unique_ptr<SkillsCrewMemberDetailsModel> skillsCrewMemberDetailsModel = std::make_unique<SkillsCrewMemberDetailsModel>();
    const std::unique_ptr<InfoCrewMemberDetailsMap> infoCrewMemberDetailsMap = std::make_unique<InfoCrewMemberDetailsMap>();
    const std::unique_ptr<EditInfoCrewMemberDetailsMap> editInfoCrewMemberDetailsMap = std::make_unique<EditInfoCrewMemberDetailsMap>();
    const std::unique_ptr<EditCurrentRoomModel> editCurrentRoomModel = std::make_unique<EditCurrentRoomModel>();
    const std::unique_ptr<EditInfoRoomDetailsMap> editInfoRoomDetailsMap = std::make_unique<EditInfoRoomDetailsMap>();
    const std::unique_ptr<EditRoomTypeModel> editRoomTypeModel = std::make_unique<EditRoomTypeModel>();
    const std::unique_ptr<CrewMemberDetailsAddSkillMap> crewMemberDetailsAddSkillMap = std::make_unique<CrewMemberDetailsAddSkillMap>();
    const std::unique_ptr<RoomDetailsEditAdjacentRoomsMap> roomDetailsEditAdjacentRoomsMap = std::make_unique<RoomDetailsEditAdjacentRoomsMap>();
};

#endif // !GAME_STATE_HPP