add_library(SpaceshipCrewV2_Lib
    STATIC
        models/room/room.cpp
        models/room/types/room_type.cpp
        models/room/types/q_models/room_type_model.cpp
        models/crew_member/crew_member.cpp
        models/space_ship/space_ship.cpp
        models/space_ship/q_models/room_list_model.cpp
        models/space_ship/q_models/crew_list_model.cpp
        models/game_state/game_state.cpp
        models/event_manager/events/create_room_event.cpp
)

target_include_directories(SpaceshipCrewV2_Lib
    PUBLIC
        util
        models/room
        models/room/types
        models/room/types/q_models/
        models/crew_member
        models/skill
        models/event
        models/space_ship
        models/space_ship/q_models
        models/event_manager
        models/event_manager/events
        models/game_state
)

add_subdirectory(qml)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

target_link_libraries(SpaceshipCrewV2_Lib
    PRIVATE
        SpaceshipCrewV2_Module
        Qt6::Core 
        Qt6::Gui 
        Qt6::Qml 
        Qt6::Quick
)