add_executable(
  hello_test
  hello_test.cpp
)

find_package(GTest REQUIRED) # Find GTest

target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)