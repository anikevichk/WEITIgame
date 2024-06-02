#include "raylib.h"
#include "Scenes/scenes.h"
#include "Tools/Window.h"

int main(){
    Image Icon = LoadImage("../src/hotdog.png");
    InitWindow(1600, 900, "EscapeFromWEITI");
    InitAudioDevice();
    Sound MenuSound = LoadSound("../src/sounds/menu.mp3");
    Sound gameOver = LoadSound("../src/sounds/gameover.mp3");
    Sound win = LoadSound("../src/sounds/winsound.mp3");
    SetWindowIcon(Icon);
    SetTargetFPS(60);
    Window currentWindow;
    currentWindow.setScreen(Window::MAIN);
    bool WinLossplayed = false;
    while (!WindowShouldClose()){

        if(currentWindow.getScreen()== Window::MAIN){
            mainScreen(currentWindow);
        }

        if(currentWindow.getScreen() == Window::Menu){
            if (!IsSoundPlaying(MenuSound))
            {
                PlaySound(MenuSound);
            }
            WinLossplayed = false;
            menu(currentWindow);
        }
        if(currentWindow.getScreen()== Window::LEVEL1){
            StopSound(MenuSound);
            level1(currentWindow);
        }

        if(currentWindow.getScreen()== Window::EXAM){
            StopSound(MenuSound);
            ExamGame(currentWindow);

        }

        if(currentWindow.getScreen()== Window::MAZE){
            StopSound(MenuSound);
            Maze(currentWindow);
        }

        if(currentWindow.getScreen()== Window::CATCH){
            StopSound(MenuSound);
            Catch(currentWindow);
        }

        if(currentWindow.getScreen()== Window::LOSS){
            if (!WinLossplayed)
            {
                WinLossplayed = true;
                PlaySound(gameOver);
            }
            lossWinScreen(currentWindow, false);
        }

        if(currentWindow.getScreen()== Window::VICTORY){
            if (!WinLossplayed)
            {
                WinLossplayed = true;
                PlaySound(win);
            }
            lossWinScreen(currentWindow);
        }
    }
    UnloadImage(Icon);
    UnloadSound(MenuSound);
    UnloadSound(win);
    UnloadSound(gameOver);

}