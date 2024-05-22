//
// Created by matve on 21.05.2024.
//
#include "raylib.h"
#include "scenes.h"
#include  "../Tools/Window.h"


int ButtonX = 550;
int ButtonY = 350;

//const char *head = "GAME OVER! :(";
const char *Text = "back to menu";
Rectangle Button = { ButtonX, ButtonY, 500, 200 };
Color color = LIGHTGRAY;

void lossWinScreen(Window& window, char *head){

    if (CheckCollisionPointRec(GetMousePosition(), Button))
    {
        color = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::Menu);
        }
    }
    else
    {
        color = LIGHTGRAY;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(head,500, 20, 100, BLACK);
    DrawRectangleRec(Button, color);
    DrawText(Text,ButtonX + 55, ButtonY + 60, 60, WHITE);
    EndDrawing();
}