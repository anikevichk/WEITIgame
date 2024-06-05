#include "DrawTools.h"

// Global variables for teacher textures
Texture2D teacher1;
Texture2D teacher2;

// Function to draw a rounded rectangle with text inside
void DrawRoundedRectangle(int posX, int posY, int width, int height, float radius, const char* text, bool& flag, Color color, const char* name) {
    // Define button properties
    int segments = 16;
    const char *ButtonText = name;
    Rectangle Button = { static_cast<float>(posX + 0.4 * width), static_cast<float>(posY + 0.6 * height), 150, 50 };
    Color ButtonColor = LIGHTGRAY;

    // Check mouse interaction with the button
    if (CheckCollisionPointRec(GetMousePosition(), Button)) {
        ButtonColor = MOUSE_LEFT_BUTTON ? RED : DARKGRAY;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            flag = false; // Set flag to false on button press
        }
    }

    // Draw rounded rectangle
    DrawRectangle(posX + radius, posY, width - 2 * radius, height, color);
    DrawRectangle(posX, posY + radius, width, height - 2 * radius, color);

    // Draw button rectangle and text
    DrawRectangleRec(Button, ButtonColor);
    DrawText(ButtonText, Button.x + 40, Button.y + 12, 30, BLACK);

    // Draw rounded corners
    DrawCircleSector((Vector2){ posX + radius, posY + radius }, radius, 180, 270, segments, color);
    DrawCircleSector((Vector2){ posX + width - radius, posY + radius }, radius, 270, 360, segments, color);
    DrawCircleSector((Vector2){ posX + radius, posY + height - radius }, radius, 90, 180, segments, color);
    DrawCircleSector((Vector2){ posX + width - radius, posY + height - radius }, radius, 0, 90, segments, color);

    // Draw side rectangles
    DrawRectangle(posX + radius, posY, width - 2 * radius, radius, color);
    DrawRectangle(posX + radius, posY + height - radius, width - 2 * radius, radius, color);
    DrawRectangle(posX, posY + radius, radius, height - 2 * radius, color);
    DrawRectangle(posX + width - radius, posY + radius, radius, height - 2 * radius, color);
}

// Function to draw teachers
void drawTeachers(bool isInRightHalf) {
    // Load teacher textures
    teacher1 = LoadTexture("../src/teacher1.png");
    teacher2 = LoadTexture("../src/teacher2.png");

    // Set scale and color based on position
    float scale1 = isInRightHalf ? 0.8f : 0.9f;
    float scale2 = isInRightHalf ? 0.9f : 0.8f;
    Color color1 = isInRightHalf ? DARKGRAY : WHITE;
    Color color2 = isInRightHalf ? WHITE : DARKGRAY;

    // Define source and destination rectangles for teachers
    Rectangle sourceRec1 = { 0.0f, 0.0f, (float)teacher1.width, (float)teacher1.height };
    Rectangle destRec1 = { 1250, 550, teacher1.width * scale1, teacher1.height * scale1 };
    Vector2 origin1 = { destRec1.width / 2.0f, destRec1.height / 2.0f };

    Rectangle sourceRec2 = { 0.0f, 0.0f, (float)teacher2.width, (float)teacher2.height };
    Rectangle destRec2 = { 315, 530, teacher2.width * scale2, teacher2.height * scale2 };
    Vector2 origin2 = { destRec2.width / 2.0f, destRec2.height / 2.0f };

    // Draw teachers with specified properties
    DrawTexturePro(teacher1, sourceRec1, destRec1, origin1, 0.0f, color1);
    DrawTexturePro(teacher2, sourceRec2, destRec2, origin2, 0.0f, color2);
}

// Function to draw a dialogue window
void DrawDialogueWindow(const char* text, int& currentLength, int textLength, int& framesCounter, Sound speaking, Texture2D& background, float letterDelay, bool& isDialogueWindowOpen, bool& isRightHalf) {
    // Draw background and teachers
    DrawTexture(background, 0, 0, WHITE);
    drawTeachers(isRightHalf);

    // Draw rounded rectangle for dialogue window
    DrawRoundedRectangle(400, 650, 900, 200, 20, text, isDialogueWindowOpen, WHITE);

    // Draw dialogue text
    DrawText(TextSubtext(text, 0, currentLength), 450, 670, 20, BLACK);

    // Play dialogue sound
    if (!IsSoundPlaying(speaking)) {
        PlaySound(speaking);
    }

    // Stop dialogue sound when text is fully displayed
    if (currentLength == textLength) {
        StopSound(speaking);
    }

    // Update frames counter and current text length
    framesCounter++;
    if (framesCounter >= letterDelay) {
        framesCounter = 0;
        if (currentLength < textLength) {
            currentLength += 2;
        }
    }
}

// Function to handle dialogue window display
void HandleDialogueWindow(const char* text, int& currentLength, int textLength, int& framesCounter, Sound speaking, Texture2D& background, float letterDelay, bool& isDialogueWindowOpen, bool& isRightHalf) {
    // Display dialogue window until it's closed or window is closed
    while (isDialogueWindowOpen && !WindowShouldClose()) {
        BeginDrawing();
        DrawDialogueWindow(text, currentLength, textLength, framesCounter, speaking, background, letterDelay, isDialogueWindowOpen, isRightHalf);
        EndDrawing();
        // Stop sound when dialogue window is closed
        if (!isDialogueWindowOpen) {
            StopSound(speaking);
        }
    }
}

// Function to unload teacher textures
void unloadTeachers() {
    UnloadTexture(teacher1);
    UnloadTexture(teacher2);
}
