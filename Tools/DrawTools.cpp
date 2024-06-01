#include "DrawTools.h"
Texture2D teacher1;
Texture2D teacher2;

void DrawRoundedRectangle(int posX, int posY, int width, int height, float radius, const char* text, bool& flag, Color color, const char* name) {
    int segments = 16;
    const char *ButtonText = name;
    Rectangle Button = { static_cast<float>(posX + 0.4 * width), static_cast<float>(posY + 0.6 * height), 150, 50 };
    Color ButtonColor = LIGHTGRAY;

    if (CheckCollisionPointRec(GetMousePosition(), Button)) {
        ButtonColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            flag = false;
        }
    }

    DrawRectangle(posX + radius, posY, width - 2 * radius, height, color);
    DrawRectangle(posX, posY + radius, width, height - 2 * radius, color);

    DrawRectangleRec(Button, ButtonColor);
    DrawText(ButtonText, Button.x + 40, Button.y + 12, 30, BLACK);

    DrawCircleSector((Vector2){ posX + radius, posY + radius }, radius, 180, 270, segments, color);
    DrawCircleSector((Vector2){ posX + width - radius, posY + radius }, radius, 270, 360, segments, color);
    DrawCircleSector((Vector2){ posX + radius, posY + height - radius }, radius, 90, 180, segments, color);
    DrawCircleSector((Vector2){ posX + width - radius, posY + height - radius }, radius, 0, 90, segments, color);

    DrawRectangle(posX + radius, posY, width - 2 * radius, radius, color);
    DrawRectangle(posX + radius, posY + height - radius, width - 2 * radius, radius, color);
    DrawRectangle(posX, posY + radius, radius, height - 2 * radius, color);
    DrawRectangle(posX + width - radius, posY + radius, radius, height - 2 * radius, color);


}

void drawTeachers(bool isInRightHalf) {
    teacher1 = LoadTexture("../src/teacher1.png");
    teacher2 = LoadTexture("../src/teacher2.png");

    float scale1 = isInRightHalf ? 0.8f : 0.9f;
    float scale2 = isInRightHalf ? 0.9f : 0.8f;
    Color color1 = isInRightHalf ? DARKGRAY : WHITE;
    Color color2 = isInRightHalf ? WHITE : DARKGRAY;

    Rectangle sourceRec1 = { 0.0f, 0.0f, (float)teacher1.width, (float)teacher1.height };
    Rectangle destRec1 = { 1250, 550, teacher1.width * scale1, teacher1.height * scale1 };
    Vector2 origin1 = { destRec1.width / 2.0f, destRec1.height / 2.0f };

    Rectangle sourceRec2 = { 0.0f, 0.0f, (float)teacher2.width, (float)teacher2.height };
    Rectangle destRec2 = { 315, 530, teacher2.width * scale2, teacher2.height * scale2 };
    Vector2 origin2 = { destRec2.width / 2.0f, destRec2.height / 2.0f };

    DrawTexturePro(teacher1, sourceRec1, destRec1, origin1, 0.0f, color1);
    DrawTexturePro(teacher2, sourceRec2, destRec2, origin2, 0.0f, color2);
}

void DrawDialogueWindow(const char* text, int& currentLength, int textLength, int& framesCounter, Sound speaking, Texture2D& background, float letterDelay, bool& isDialogueWindowOpen, bool& isRightHalf) {
    DrawTexture(background, 0, 0, WHITE);
    drawTeachers(isRightHalf);
    DrawRoundedRectangle(400, 650, 900, 200, 20, text, isDialogueWindowOpen, WHITE);

    DrawText(TextSubtext(text, 0, currentLength), 450, 670, 20, BLACK);
    if (!IsSoundPlaying(speaking)) {
        PlaySound(speaking);
    }
    if (currentLength == textLength) {
        StopSound(speaking);
    }
    framesCounter++;
    if (framesCounter >= letterDelay) {
        framesCounter = 0;
        if (currentLength < textLength)
            currentLength++;
    }

}

void unloadTeachers() {
    UnloadTexture(teacher1);
    UnloadTexture(teacher2);
}