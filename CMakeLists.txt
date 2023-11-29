cmake_minimum_required(VERSION 3.20)
project(regexp-parser)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_FLAGS "-O0 -coverage")

find_program(LCOV lcov REQUIRED)
find_program(GENHTML genhtml REQUIRED)

add_custom_target(coverage
  COMMAND ${LCOV} --directory . --capture --output-file coverage.info
  COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})



enable_testing()

add_executable(regexp-parser src/applier.h src/main.cpp)
add_executable(tests  tests/run_tests.cpp tests/tests.cpp)

target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
add_test(unit_test tests)