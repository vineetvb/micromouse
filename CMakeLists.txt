cmake_minimum_required(VERSION 3.8)
project(Micromouse)

set(SOURCES main.cpp maze.cpp mouse.cpp sensor.cpp)
set(CMAKE_CXX_FLAGS "-std=c++1y -O0 -g")


# X11 is required
find_package(X11 REQUIRED)
message(STATUS X11_FOUND)
include_directories(${X11_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

add_executable(micromouse ${SOURCES})

target_link_libraries(micromouse m pthread ${X11_LIBRARIES})
