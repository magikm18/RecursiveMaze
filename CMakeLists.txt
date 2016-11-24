cmake_minimum_required(VERSION 3.6)
project(RecursiveMaze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(RecursiveMaze ${SOURCE_FILES})