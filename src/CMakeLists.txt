add_library(SpaceshipCrewV2_Lib
    STATIC
        models/room/room.cpp
        models/crew_member/crew_member.cpp
        models/space_ship/space_ship.cpp
)

target_include_directories(SpaceshipCrewV2_Lib
    PUBLIC
        models/room
        models/room/types
        models/crew_member
        models/skill
        models/event
        models/space_ship
)

add_subdirectory(qml)

target_link_libraries(SpaceshipCrewV2_Lib
    PRIVATE
        SpaceshipCrewV2_Module
)