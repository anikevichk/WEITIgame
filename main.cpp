#include "raylib.h"
#include "Scenes/scenes.h"
#include "Tools/Window.h"

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

        if(currentWindow.getScreen()== Window::EXAM){
            ExamGame(currentWindow);
        }


        if(currentWindow.getScreen()== Window::MAZE){
            Maze(currentWindow);
        }

        if(currentWindow.getScreen()== Window::LOSS){
            lossWinScreen(currentWindow, "GAME OVER!:(");
        }

        if(currentWindow.getScreen()== Window::VICTORY){
            lossWinScreen(currentWindow, "VICTORY!");
        }
    }

}