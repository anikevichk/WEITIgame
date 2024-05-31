#include "raylib.h"
#include "Scenes/scenes.h"
#include "Tools/Window.h"

int main() {
    Image Icon = LoadImage("../src/hotdog.png");
    InitWindow(1600, 900, "EscapeFromWEITI");
    InitAudioDevice();

    Sound MenuSound = LoadSound("../src/sounds/menu.mp3");
    Sound gameOver = LoadSound("../src/sounds/gameover.mp3");
    Sound win = LoadSound("../src/sounds/win.mp3");
    SetSoundVolume(win, 0.5);

    SetWindowIcon(Icon);
    SetTargetFPS(60);

    Window currentWindow;
    currentWindow.setScreen(Window::Menu);

    int currentScreen = Window::Menu;
    PlaySound(MenuSound);

    while (!WindowShouldClose()) {
        int newScreen = currentWindow.getScreen();

        if (newScreen != currentScreen) {
            StopSound(MenuSound);
            StopSound(gameOver);
            StopSound(win);

            switch (newScreen) {
                case Window::Menu:
                    PlaySound(MenuSound);
                    break;
                case Window::LEVEL1:
                case Window::EXAM:
                case Window::MAZE:
                case Window::CATCH:
                    break;
                case Window::LOSS:
                    PlaySound(gameOver);
                    break;
                case Window::VICTORY:
                    PlaySound(win);
                    break;
            }
            currentScreen = newScreen;
        }


        if (currentWindow.getScreen() == Window::Menu) {
            menu(currentWindow);
        }
        else if (currentWindow.getScreen() == Window::LEVEL1) {
            level1(currentWindow);
        }
        else if (currentWindow.getScreen() == Window::EXAM) {
            ExamGame(currentWindow);
        }
        else if (currentWindow.getScreen() == Window::MAZE) {
            Maze(currentWindow);
        }
        else if (currentWindow.getScreen() == Window::CATCH) {
            Catch(currentWindow);
        }
        else if (currentWindow.getScreen() == Window::LOSS) {
            lossWinScreen(currentWindow, "GAME OVER!:(");
        }
        else if (currentWindow.getScreen() == Window::VICTORY) {
            lossWinScreen(currentWindow, "VICTORY!");
        }
    }

    UnloadImage(Icon);
    UnloadSound(MenuSound);
    UnloadSound(gameOver);
    UnloadSound(win);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
