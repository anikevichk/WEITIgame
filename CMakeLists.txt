cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
        levels/RunnerLevel/levelRunner.cpp
        Scenes/menu.cpp
        Tools/Window.h
        Tools/Window.cpp
        Scenes/LossWinScreen.cpp
        Scenes/scenes.h
        levels/ExamGameLevel/ExamGame.cpp
        levels/ExamGameLevel/enemy.cpp
        levels/ExamGameLevel/enemy.h
        Scenes/mainScreen.cpp
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
        levels/CatchLevel/catch.h
        levels/CatchLevel/collision.cpp
        levels/CatchLevel/collision.h
        levels/CatchLevel/renderer.cpp
        levels/CatchLevel/renderer.h
        levels/CatchLevel/resourceManager.cpp
        levels/CatchLevel/resourceManager.h

        Tools/DrawTools.h
        Tools/DrawTools.cpp
        levels/ExamGameLevel/Player.h
        levels/ExamGameLevel/Player.cpp
        levels/ExamGameLevel/levelManager.h
        levels/ExamGameLevel/levelManager.cpp
        levels/RunnerLevel/LevelManager.h
        levels/RunnerLevel/LevelManager.cpp
        levels/RunnerLevel/Structs.h
)
set(TEST_SOURCES
        Tests/testCatch/testCollision.cpp
        Tests/testMaze/testGenerator.cpp
        Tests/testMaze/testPlayer.cpp

        levels/MazeLevel/renderer.cpp
        levels/MazeLevel/player.cpp
        levels/MazeLevel/mazeGenerator.cpp
        levels/RunnerLevel/LevelManager.cpp
        levels/CatchLevel/resourceManager.cpp
        levels/CatchLevel/collision.cpp
        levels/CatchLevel/renderer.cpp
        Tools/Window.cpp
)
add_executable(main main.cpp ${PROJECT_SOURCES})
add_executable(tests ${TEST_SOURCES})

find_package(raylib CONFIG REQUIRED)
target_link_libraries(main PRIVATE raylib)
target_link_libraries(tests PRIVATE raylib)
target_link_libraries(tests PUBLIC gtest_main)
