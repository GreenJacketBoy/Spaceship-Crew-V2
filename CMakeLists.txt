cmake_minimum_required(VERSION 4.3.1)
project(SpaceshipCrewV2)

# add_library(SpaceshipCrewV2
#   src/app.cpp
# )

# target_compile_features(SpaceshipCrewV2 PUBLIC cxx_std_20)
# target_include_directories(SpaceshipCrewV2
#   PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Qml) # Find Qt6
find_package(GTest REQUIRED) # Find GTest

add_executable(SpaceshipCrewV2_cli src/main.cpp)
target_link_libraries(SpaceshipCrewV2_cli 
  PRIVATE 
    # SpaceshipCrewV2
    Qt6::Qml
    # GTest::gtest_main
)

get_target_property(QT_INCLUDES SpaceshipCrewV2_cli INCLUDE_DIRECTORIES)
message(STATUS "Include dirs for hello_qt: ${QT_INCLUDES}")

add_subdirectory(tests)