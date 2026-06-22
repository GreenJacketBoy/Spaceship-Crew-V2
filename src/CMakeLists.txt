add_library(SpaceshipCrewV2_Lib
    STATIC
        models/room/room.cpp
)

target_include_directories(SpaceshipCrewV2_Lib
    PUBLIC
        models/room
        models/room/types
)

add_subdirectory(qml)

target_link_libraries(SpaceshipCrewV2_Lib
    PRIVATE
        SpaceshipCrewV2_Module
)