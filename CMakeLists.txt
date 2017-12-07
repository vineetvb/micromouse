cmake_minimum_required(VERSION 3.9)
project(Micromouse)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV " ${OpenCV_FOUND})
set(SOURCES main.cpp maze.cpp mouse.cpp)
set(CMAKE_CXX_FLAGS "-std=c++14 -O0 -g")

add_executable(micromouse ${SOURCES})
