cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)


add_executable(main main.cpp
        level1.cpp
        level1.h
        menu.cpp
        Window.h
        Window.cpp
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(main PRIVATE raylib)
