cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "clang compiler" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "clang++ compiler" FORCE)
project(google_test CXX)
find_package(GTest)
file(GLOB_RECURSE SRC_FILES RELATIVE /workspace src/*/*.cpp)
list(FILTER SRC_FILES EXCLUDE REGEX ".*impl.cpp")
message(STATUS "Target source files: ${SRC_FILES}")
file(GLOB_RECURSE TEST_FILES RELATIVE /workspace test/*/*_test.cpp)
message(STATUS "Test files: ${TEST_FILES}")
add_executable(
    google_test
    ${SRC_FILES}
    ${TEST_FILES}
)
target_link_libraries(
    google_test
    ${GTEST_BOTH_LIBRARIES}
    gmock
    pthread
    GTest::Main
    )
target_include_directories(google_test PUBLIC ${GTEST_INCLUDE_DIRS})
target_include_directories(google_test PUBLIC
    src/host_communication
    src/sensor_communication
    test/host_communication
    test/sensor_communication
)
