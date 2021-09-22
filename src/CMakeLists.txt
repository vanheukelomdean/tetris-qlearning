project(game)

find_package(SDL2 REQUIRED)
include_directories(
    ${PROJECT_SOURCE_DIR}, 
    ${SDL2_INCLUDE_DIRS}
)

add_executable(
    ${PROJECT_NAME} 
    Game.cpp 
    Control.cpp 
    Tetromino.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)