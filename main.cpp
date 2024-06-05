#include "raylib.h"
#include "Scenes/scenes.h"
#include "Tools/Window.h"

int main() {
    // Initialize window and audio device
    Image Icon = LoadImage("../src/hotdog.png");
    InitWindow(1600, 900, "EscapeFromWEITI");
    InitAudioDevice();

    // Load sounds and set window icon
    Sound MenuSound = LoadSound("../src/sounds/menu.mp3");
    Sound gameOver = LoadSound("../src/sounds/gameover.mp3");
    Sound win = LoadSound("../src/sounds/winsound.mp3");
    SetWindowIcon(Icon);
    SetTargetFPS(60);

    // Initialize current window and flag for Win/Loss sound playing
    Window currentWindow;
    currentWindow.setScreen(Window::MAIN);
    bool WinLossplayed = false;

    // Main game loop
    while (!WindowShouldClose()) {
        // Check current window state and update accordingly
        if(currentWindow.getScreen() == Window::MAIN) {
            mainScreen(currentWindow);
        } else if(currentWindow.getScreen() == Window::Menu) {
            // Play menu sound if not already playing
            if (!IsSoundPlaying(MenuSound)) {
                PlaySound(MenuSound);
            }
            WinLossplayed = false;
            menu(currentWindow);
        } else if(currentWindow.getScreen() == Window::LEVEL1) {
            StopSound(MenuSound);
            level1(currentWindow);
        } else if(currentWindow.getScreen() == Window::EXAM) {
            StopSound(MenuSound);
            ExamGame(currentWindow);
        } else if(currentWindow.getScreen() == Window::MAZE) {
            StopSound(MenuSound);
            Maze(currentWindow);
        } else if(currentWindow.getScreen() == Window::CATCH) {
            StopSound(MenuSound);
            Catch(currentWindow);
        } else if(currentWindow.getScreen() == Window::LOSS) {
            // Play game over sound if not already playing
            if (!WinLossplayed) {
                WinLossplayed = true;
                PlaySound(gameOver);
            }
            lossWinScreen(currentWindow, false);
        } else if(currentWindow.getScreen() == Window::VICTORY) {
            // Play victory sound if not already playing
            if (!WinLossplayed) {
                WinLossplayed = true;
                PlaySound(win);
            }
            lossWinScreen(currentWindow);
        }
    }

    // Unload resources and close window
    UnloadImage(Icon);
    UnloadSound(MenuSound);
    UnloadSound(win);
    UnloadSound(gameOver);

    CloseWindow();

    return 0;
}
