cmake_minimum_required(VERSION 4.3.1)
project(SpaceshipCrewV2)

set(CMAKE_AUTOMOC ON) # DOESN'T WORK WITHOUT IT (https://doc.qt.io/qt-6/moc.html)
# set(CMAKE_AUTORCC ON) # https://doc.qt.io/qt-6/resources.html

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_subdirectory(src/SpaceshipCrewV2_Dir)

# Set up the executable
qt_add_executable(SpaceshipCrewV2_Bin
    main.cpp
)

target_link_libraries(SpaceshipCrewV2_Bin
    PRIVATE 
        Qt6::Core 
        Qt6::Gui 
        Qt6::Qml 
        Qt6::Quick
        SpaceshipCrewV2_Module
)

# Note to myself and others learning :
# As I found out, the "ctest" command must be ran from the build directory, but
# more than that, it must be ran from the build directory mirroring the code 
# directory containing the CMakeLists.txt file where "enable_testing()" is called.
# If it's in /test/CMakeLists.txt then you have to do "cd build/test" followed
# by "ctest"
enable_testing()
add_subdirectory(tests)