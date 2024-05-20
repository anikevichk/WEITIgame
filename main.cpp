#include "raylib.h"
#include "level1.h"
#include "menu.h"
#include <iostream>
#include "Window.h"

int main(){
    InitWindow(1600, 900, "EscapeFromWEITI");
    SetTargetFPS(60);
    Window currentWindow;
    currentWindow.setScreen(Window::Menu);

    while (!WindowShouldClose()){
        if(currentWindow.getScreen() == Window::Menu){
        menu(currentWindow);
        }
        if(currentWindow.getScreen()== Window::LEVEL1){
            level1(currentWindow);
        }

    }

}