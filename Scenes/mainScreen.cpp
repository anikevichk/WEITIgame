#include "raylib.h"
#include "scenes.h"
#include "../Tools/Window.h"

void mainScreen(Window& window) {
    int ButtonX = 650;
    int buttonMenuY = 450;
    int buttonExitY = 600;

    const char *textMenu = "Menu";
    const char *textExit = "Exit";
    Rectangle ButtonMenu = { static_cast<float>(ButtonX), static_cast<float>(buttonMenuY), 300.0f, 100.0f };
    Rectangle ButtonExit = { static_cast<float>(ButtonX), static_cast<float>(buttonExitY), 300.0f, 100.0f };
    Color orange = {236, 131, 48, 255};
    Color darkOrange = {153, 77, 16, 255};
    Color colorMenu, colorExit;

    Texture2D background = LoadTexture("../src/mainScreen.png");
    Sound MenuSound = LoadSound("../src/sounds/main2.mp3");
    SetSoundVolume(MenuSound, 0.5);


    while (!WindowShouldClose() && window.getScreen() == Window::MAIN) {

        if (!IsSoundPlaying(MenuSound))
        {
            PlaySound(MenuSound);
        }

        if (CheckCollisionPointRec(GetMousePosition(), ButtonMenu)) {
            colorMenu = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? darkOrange : darkOrange;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                window.setScreen(Window::Menu);
            }
        } else {
            colorMenu = orange;
        }

        if (CheckCollisionPointRec(GetMousePosition(), ButtonExit)) {
            colorExit = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? darkOrange : darkOrange;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
            }
        } else {
            colorExit = orange;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(ButtonMenu, colorMenu);
        DrawRectangleRec(ButtonExit, colorExit);
        DrawText(textMenu, ButtonX + 75, buttonMenuY + 20, 60, WHITE);
        DrawText(textExit, ButtonX + 90, buttonExitY + 20, 60, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadSound(MenuSound);
}
