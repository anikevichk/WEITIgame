#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "scenes.h"
#include "../Tools/Window.h"

// Display the loss or win screen with a button to return to the menu
void lossWinScreen(Window& window, bool win) {
    // Button properties
    int buttonX = 550;
    int buttonY = 500;
    const char *text = "Back to Menu";
    Rectangle button = { static_cast<float>(buttonX), static_cast<float>(buttonY), 500.0f, 100.0f };

    // Load textures for win and loss screens
    Texture2D winScreen = LoadTexture("../src/victory.png");
    Texture2D lossScreen = LoadTexture("../src/gameOver.png");

    // Define colors for the button and hover effect
    Color green = { 17, 70, 23, 255 };     // Light green
    Color red = { 102, 37, 37, 255 };       // Light red

    Color darkGreen = { 6, 46, 10, 255 };   // Dark green (for hover effect)
    Color darkRed = { 66, 12, 12, 255 };    // Dark red (for hover effect)

    // Determine base and hover colors based on win condition
    Color baseColor = win ? green : red;    // Base color changes depending on win or loss
    Color hoverColor = win ? darkGreen : darkRed; // Hover color changes accordingly

    Color color = baseColor; // Initialize button color with the base color


    // Check if mouse hovers over the button
    if (CheckCollisionPointRec(GetMousePosition(), button)) {
        color = hoverColor;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            color = baseColor;
            window.setScreen(Window::Menu); // Return to menu on button click
        }
    }

    // Draw the screen
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (win) {
        DrawTexture(winScreen, 0, 0, WHITE);
    } else {
        DrawTexture(lossScreen, 0, 0, WHITE);
    }
    DrawRectangleRec(button, color); // Draw button
    DrawText(text, buttonX + 55, buttonY + 25, 60, WHITE); // Draw button text
    EndDrawing();

    // Unload textures
    UnloadTexture(winScreen);
    UnloadTexture(lossScreen);
}
