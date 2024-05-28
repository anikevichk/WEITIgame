
#include "DrawTools.h"

void DrawRoundedRectangle(int posX, int posY, int width, int height, float radius, const char* text,bool& flag, Color color ) {
    int segments = 16;
    const char *ButtonText = "OK";
    Rectangle Button = {static_cast<float>(posX + 0.25*width), static_cast<float>(posY+0.75*height), 100, 50 };
    Color ButtonColor = LIGHTGRAY;

    if (CheckCollisionPointRec(GetMousePosition(), Button))
    {
        ButtonColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            flag = false;
        }
    }

    DrawRectangle(posX + radius, posY, width - 2 * radius, height, color);
    DrawRectangle(posX, posY + radius, width, height - 2 * radius, color);

    DrawRectangleRec(Button, ButtonColor);
    DrawText(ButtonText,Button.x + 30, Button.y + 12, 30, BLACK );

    DrawCircleSector((Vector2){posX + radius, posY + radius}, radius, 180, 270, segments, color);
    DrawCircleSector((Vector2){posX + width - radius, posY + radius}, radius, 270, 360, segments, color);
    DrawCircleSector((Vector2){posX + radius, posY + height - radius}, radius, 90, 180, segments, color);
    DrawCircleSector((Vector2){posX + width - radius, posY + height - radius}, radius, 0, 90, segments, color);

    DrawRectangle(posX + radius, posY, width - 2 * radius, radius, color);
    DrawRectangle(posX + radius, posY + height - radius, width - 2 * radius, radius, color);
    DrawRectangle(posX, posY + radius, radius, height - 2 * radius, color);
    DrawRectangle(posX + width - radius, posY + radius, radius, height - 2 * radius, color);
    DrawText(text, posX+10, posY+10, 15, BLACK);
}
