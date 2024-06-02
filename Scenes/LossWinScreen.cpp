#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "scenes.h"
#include "../Tools/Window.h"

void lossWinScreen(Window& window, bool win) {
    int ButtonX = 550;
    int ButtonY = 500;

    const char *Text = "back to menu";
    Rectangle Button = { static_cast<float>(ButtonX), static_cast<float>(ButtonY), 500.0f, 100.0f };

    Texture2D winScreen = LoadTexture("../src/victory.png");
    Texture2D lossScreen = LoadTexture("../src/gameOver.png");

    Color green = { 17, 70, 23, 255 };
    Color red = { 102, 37, 37, 255 };

    Color darkGreen = { 6, 46, 10, 255 };
    Color darkRed = { 66, 12, 12, 255 };

    Color baseColor = win ? green : red;
    Color hoverColor = win ? darkGreen : darkRed;
    Color color = baseColor;

    if (CheckCollisionPointRec(GetMousePosition(), Button)) {
        color = hoverColor;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            color = baseColor;
            window.setScreen(Window::Menu);
        }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (win) {
        DrawTexture(winScreen, 0, 0, WHITE);
    } else {
        DrawTexture(lossScreen, 0, 0, WHITE);
    }
    DrawRectangleRec(Button, color);
    DrawText(Text, ButtonX + 55, ButtonY + 25, 60, WHITE);
    EndDrawing();

    UnloadTexture(winScreen);
    UnloadTexture(lossScreen);
}
