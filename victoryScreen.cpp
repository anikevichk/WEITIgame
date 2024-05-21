//
// Created by matve on 21.05.2024.
//
//
// Created by matve on 21.05.2024.
//
#include "raylib.h"
#include "victoryScreen.h"
#include  "Window.h"


int X = 550;
int Y = 350;

const char *Head = "VICTORY! Ja lybly Sonyu";
const char *text = "back to menu";
Rectangle VButton = { X, Y, 500, 200 };
Color BColor = LIGHTGRAY;

void victoryScreen(Window& window){

    if (CheckCollisionPointRec(GetMousePosition(), VButton))
    {
        BColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::Menu);
        }
    }
    else
    {
        BColor = LIGHTGRAY;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(Head,550, 20, 100, BLACK);
    DrawRectangleRec(VButton, BColor);
    DrawText(text,X + 55, Y + 60, 60, WHITE);
    EndDrawing();
}