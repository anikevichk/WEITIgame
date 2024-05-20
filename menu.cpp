#include "raylib.h"
#include "menu.h"
#include "level1.h"
#include  "Window.h"

int buttonX = 100;
int buttonY = 200;

typedef enum GameScreen { Menu, LEVEL1 } GameScreen;

const char *header = "CHOOSE LEVEL:";
const char *buttonText = "1";
Rectangle button = { buttonX, buttonY, 100, 50 };
Color buttonColor = LIGHTGRAY;

void menu(Window& window) {
    if (CheckCollisionPointRec(GetMousePosition(), button))
    {
        buttonColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            window.setScreen(Window::LEVEL1);
        }
    }
    else
    {
        buttonColor = LIGHTGRAY;
    }
//        std::cout <<"soneczka samaja luczszaja hihihi"<<std::endl;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(header,600, 20, 40, BLACK);
    DrawRectangleRec(button, buttonColor);
    DrawText(buttonText,buttonX + 45, buttonY + 12, 30, WHITE);
    EndDrawing();
}
