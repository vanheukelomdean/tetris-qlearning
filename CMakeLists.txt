cmake_minimum_required(VERSION 3.21.3)

project(Tetris)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory (src)

enable_testing ()
add_subdirectory (test)
