#include "raylib.h"
#include "scenes.h"
#include "../Tools/Window.h"

// Display the main screen with menu and exit buttons
void mainScreen(Window& window) {
    // Button properties
    int buttonX = 650;
    int buttonMenuY = 450;
    int buttonExitY = 600;
    const char *textMenu = "Menu";
    const char *textExit = "Exit";
    Rectangle buttonMenu = { static_cast<float>(buttonX), static_cast<float>(buttonMenuY), 300.0f, 100.0f };
    Rectangle buttonExit = { static_cast<float>(buttonX), static_cast<float>(buttonExitY), 300.0f, 100.0f };

    // Button colors
    Color orange = {236, 131, 48, 255};
    Color darkOrange = {153, 77, 16, 255};
    Color colorMenu, colorExit;

    // Load background texture and menu sound
    Texture2D background = LoadTexture("../src/mainScreen.png");
    Sound menuSound = LoadSound("../src/sounds/main2.mp3");
    SetSoundVolume(menuSound, 0.5);

    // Main loop for the main screen
    while (!WindowShouldClose() && window.getScreen() == Window::MAIN) {
        // Play menu sound if not playing
        if (!IsSoundPlaying(menuSound)) {
            PlaySound(menuSound);
        }

        // Check mouse interaction with menu and exit buttons
        if (CheckCollisionPointRec(GetMousePosition(), buttonMenu)) {
            colorMenu = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? darkOrange : darkOrange;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                window.setScreen(Window::Menu);
            }
        } else {
            colorMenu = orange;
        }

        if (CheckCollisionPointRec(GetMousePosition(), buttonExit)) {
            colorExit = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? darkOrange : darkOrange;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
            }
        } else {
            colorExit = orange;
        }

        // Draw the main screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(buttonMenu, colorMenu);
        DrawRectangleRec(buttonExit, colorExit);
        DrawText(textMenu, buttonX + 75, buttonMenuY + 20, 60, WHITE);
        DrawText(textExit, buttonX + 90, buttonExitY + 20, 60, WHITE);
        EndDrawing();
    }

    // Unload resources
    UnloadTexture(background);
    UnloadSound(menuSound);
}
