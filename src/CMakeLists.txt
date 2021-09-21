cmake_minimum_required(VERSION 3.21.3)

project("tetris")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Game Game.cpp)
target_link_libraries(Game ${SDL2_LIBRARIES})