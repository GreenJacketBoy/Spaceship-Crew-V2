add_executable(spaceship_test
    hello_test.cpp
    room_test.cpp
    crew_member_test.cpp
    skill_test.cpp
)

find_package(GTest REQUIRED) # Find GTest

target_link_libraries(spaceship_test
    GTest::gtest_main
    SpaceshipCrewV2_Lib
)

target_compile_options(spaceship_test PRIVATE --coverage)
target_link_options(spaceship_test PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(spaceship_test)
