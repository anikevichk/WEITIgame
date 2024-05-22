#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "scenes.h"
#include  "../Tools/Window.h"

int buttonX = 100;
int buttonY = 200;

int buttonTetrisX = 250;
int buttonMazeX = 400;

//typedef enum GameScreen { Menu, LEVEL1 } GameScreen;

const char *header = "CHOOSE LEVEL:";
const char *button1Text = "1";
const char *buttonTetrisText = "2";
const char *buttonMazetxt = "3";
Rectangle button1 = {buttonX, buttonY, 100, 50 };
Rectangle buttonTetris = {buttonTetrisX, buttonY, 100, 50 };
Rectangle buttonMaze = {buttonMazeX, buttonY, 100, 50};

Color button1Color = LIGHTGRAY;
Color buttonTetrisColor = LIGHTGRAY;
Color buttonMazeColor = LIGHTGRAY;


void menu(Window& window) {
    if (CheckCollisionPointRec(GetMousePosition(), button1))
    {
        button1Color = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::LEVEL1);
        }
    }
    else
    {
        button1Color = LIGHTGRAY;
    }


    if (CheckCollisionPointRec(GetMousePosition(), buttonTetris))
    {
        buttonTetrisColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::EXAM);
        }
    }
    else
    {
        buttonTetrisColor = LIGHTGRAY;
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

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(header,600, 20, 40, BLACK);

    DrawRectangleRec(button1, button1Color);
    DrawText(button1Text, buttonX + 45, buttonY + 12, 30, WHITE);

    DrawRectangleRec(buttonTetris, buttonTetrisColor);
    DrawText(buttonTetrisText, buttonTetrisX + 45, buttonY + 12, 30, WHITE);

    DrawRectangleRec(buttonMaze, buttonMazeColor);
    DrawText(buttonMazetxt, buttonMazeX + 45, buttonY + 12, 30, WHITE);

    EndDrawing();
}
