cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)



add_executable(main main.cpp
        levels/RunnerLevel/level1.cpp
        Scenes/menu.cpp
        Tools/Window.h
        Tools/Window.cpp
        Scenes/LossWinScreen.cpp
        Scenes/scenes.h
        levels/ExamGameLevel/ExamGame.cpp
        levels/MazeLevel/maze.cpp
        levels/MazeLevel/maze.h
        levels/ExamGameLevel/enemy.cpp
        levels/ExamGameLevel/enemy.h
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(main PRIVATE raylib)
