#include "raylib.h"
#include "scenes.h"
#include "../Tools/Window.h"

// Button properties
int buttonY = 450;
int buttonRunnerX = 230;
int buttonMazeX = buttonRunnerX + 300;
int buttonCatchX = buttonMazeX + 300;
int buttonExamX = buttonCatchX + 300;

// Button texts
const char *buttonRunnertxt = "Heading\n\nto Weiti";
const char *buttonMazetxt = "First day";
const char *buttonCatchtxt = "Preparation";
const char *buttonExamtxt = "Exam";

// Button rectangles
Rectangle buttonRunner = { buttonRunnerX, buttonY, 250, 150 };
Rectangle buttonMaze = { buttonMazeX, buttonY, 250, 150 };
Rectangle buttonCatch = { buttonCatchX, buttonY, 250, 150 };
Rectangle buttonExam = { buttonExamX, buttonY, 250, 150 };

// Button colors
Color blue = { 74, 140, 182, 255 };
Color darkBlue = { 24, 81, 118, 255 };
Color buttonRunnerColor, buttonExamColor, buttonMazeColor, buttonCatchColor;

// Load menu sound
Sound MenuSound = LoadSound("../src/sounds/menu.mp3");

// Display the menu screen
void menu(Window& window) {
    // Load background texture
    Texture2D background = LoadTexture("../src/chooseLevel.png");

    // Check mouse interaction with each button
    if (CheckCollisionPointRec(GetMousePosition(), buttonRunner)) {
        buttonRunnerColor = MOUSE_LEFT_BUTTON ? RED : darkBlue;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::LEVEL1); // Switch to level 1 screen on button click
            UnloadSound(MenuSound);
        }
    } else {
        buttonRunnerColor = blue;
    }

    if (CheckCollisionPointRec(GetMousePosition(), buttonExam)) {
        buttonExamColor = MOUSE_LEFT_BUTTON ? RED : darkBlue;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::EXAM); // Switch to exam screen on button click
            UnloadSound(MenuSound);
        }
    } else {
        buttonExamColor = blue;
    }

    if (CheckCollisionPointRec(GetMousePosition(), buttonMaze)) {
        buttonMazeColor = MOUSE_LEFT_BUTTON ? RED : darkBlue;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::MAZE); // Switch to maze screen on button click
            UnloadSound(MenuSound);
        }
    } else {
        buttonMazeColor = blue;
    }

    if (CheckCollisionPointRec(GetMousePosition(), buttonCatch)) {
        buttonCatchColor = MOUSE_LEFT_BUTTON ? RED : darkBlue;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::CATCH); // Switch to catch screen on button click
            UnloadSound(MenuSound);
        }
    } else {
        buttonCatchColor = blue;
    }

    // Play menu sound
    PlaySound(MenuSound);

    // Draw the menu screen
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);

    DrawRectangleRec(buttonRunner, buttonRunnerColor);
    DrawText(buttonRunnertxt, buttonRunnerX + 70, buttonY + 40, 30, WHITE);

    DrawRectangleRec(buttonMaze, buttonMazeColor);
    DrawText(buttonMazetxt, buttonMazeX + 55, buttonY + 60, 30, WHITE);

    DrawRectangleRec(buttonCatch, buttonCatchColor);
    DrawText(buttonCatchtxt, buttonCatchX + 35, buttonY + 60, 30, WHITE);

    DrawRectangleRec(buttonExam, buttonExamColor);
    DrawText(buttonExamtxt, buttonExamX + 90, buttonY + 60, 30, WHITE);
    EndDrawing();

    // Unload resources
    UnloadTexture(background);
}
