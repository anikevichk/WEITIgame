#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "scenes.h"
#include  "../Tools/Window.h"

int buttonY = 200;

int buttonRunnerX = 100;
int buttonExamX = 250;
int buttonMazeX = 400;
int buttonCatchX = 550;

const char *header = "CHOOSE LEVEL:";

const char *buttonRunnertxt = "1";
const char *buttonExamtxt = "2";
const char *buttonMazetxt = "3";
const char *buttonCatchtxt = "4";

Rectangle buttonRunner = {buttonRunnerX, buttonY, 100, 50 };
Rectangle buttonExam = {buttonExamX, buttonY, 100, 50 };
Rectangle buttonMaze = {buttonMazeX, buttonY, 100, 50};
Rectangle buttonCatch = {buttonCatchX, buttonY, 100, 50};

Color buttonRunnerColor = LIGHTGRAY;
Color buttonExamColor = LIGHTGRAY;
Color buttonMazeColor = LIGHTGRAY;
Color buttonCatchColor = LIGHTGRAY;


void menu(Window& window) {
    if (CheckCollisionPointRec(GetMousePosition(), buttonRunner))
    {
        buttonRunnerColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::LEVEL1);
        }
    }
    else
    {
        buttonRunnerColor = LIGHTGRAY;
    }


    if (CheckCollisionPointRec(GetMousePosition(), buttonExam))
    {
        buttonExamColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::EXAM);
        }
    }
    else
    {
        buttonExamColor = LIGHTGRAY;
    }

    if (CheckCollisionPointRec(GetMousePosition(), buttonMaze))
    {
        buttonMazeColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::MAZE);
        }
    }
    else
    {
        buttonMazeColor = LIGHTGRAY;
    }

    if (CheckCollisionPointRec(GetMousePosition(), buttonCatch))
    {
        buttonCatchColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::CATCH);
        }
    }
    else
    {
        buttonCatchColor = LIGHTGRAY;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(header,600, 20, 40, BLACK);

    DrawRectangleRec(buttonRunner, buttonRunnerColor);
    DrawText(buttonRunnertxt, buttonRunnerX + 45, buttonY + 12, 30, WHITE);

    DrawRectangleRec(buttonExam, buttonExamColor);
    DrawText(buttonExamtxt, buttonExamX + 45, buttonY + 12, 30, WHITE);

    DrawRectangleRec(buttonMaze, buttonMazeColor);
    DrawText(buttonMazetxt, buttonMazeX + 45, buttonY + 12, 30, WHITE);

    DrawRectangleRec(buttonCatch, buttonCatchColor);
    DrawText(buttonCatchtxt, buttonCatchX + 45, buttonY + 12, 30, WHITE);
    EndDrawing();
}
