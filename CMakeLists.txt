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
        levels/ExamGameLevel/enemy.cpp
        levels/ExamGameLevel/enemy.h

        levels/MazeLevel/maze.cpp
        levels/MazeLevel/mazeGenerator.cpp
        levels/MazeLevel/mazeGenerator.h
        levels/MazeLevel/player.cpp
        levels/MazeLevel/player.h
        levels/MazeLevel/renderer.cpp
        levels/MazeLevel/renderer.h
        levels/MazeLevel/resourceManager.cpp
        levels/MazeLevel/resourceManager.h
        levels/MazeLevel/cell.h

        levels/CatchLevel/catch.cpp
        Tools/DrawTools.h
        Tools/DrawTools.cpp
        levels/ExamGameLevel/Player.h
        levels/ExamGameLevel/Player.cpp
        levels/ExamGameLevel/levelManager.h
        levels/ExamGameLevel/levelManager.cpp
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(main PRIVATE raylib)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY      https://github.com/google/googletest.git
#        GIT_TAG main
#)
#FetchContent_MakeAvailable(googletest)
#
#set(SOURCES
#        levels/MazeLevel/maze.h
#        levels/MazeLevel/maze.cpp
#        tests/test_maze.cpp
#)
#
#add_executable(maze ${SOURCES})
#target_link_libraries(maze PUBLIC gtest_main)
