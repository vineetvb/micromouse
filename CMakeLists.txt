cmake_minimum_required(VERSION 3.8)
project(Micromouse)

set(SOURCES algorithm.cpp main.cpp maze.cpp mouse.cpp sensor.cpp simulation.cpp)
set(CMAKE_CXX_FLAGS "-std=c++1y -O0 -g")

# X11 is required.
find_package(X11 REQUIRED)
message(STATUS X11_FOUND)
include_directories(${X11_INCLUDE_DIR})

# Enable GTest Testing Framework.
enable_testing()
find_package(GTest REQUIRED)

# Include Cimg for plotting and viz.
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

add_library(micromouse ${SOURCES})

# Main Executable to run the simulator
add_executable(run_micromouse main.cpp)
target_link_libraries(run_micromouse micromouse m pthread ${X11_LIBRARIES})

# Unit Testing of the libraries
# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
include_directories(GTEST_INCLUDE_DIRS)
add_executable(run_tests maze_test.cpp algorithm_test.cpp)
target_link_libraries(run_tests GTest::GTest GTest::Main micromouse)
gtest_add_tests(
        TARGET      run_tests
        TEST_SUFFIX _test
        TEST_LIST   noArgsTests
        )