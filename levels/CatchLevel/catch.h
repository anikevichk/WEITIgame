#include "raylib.h"

#ifndef CATCH_H
#define CATCH_H
int screenWidth = 1600;
int screenHeight = 900;
int maxFruits = 20;

int currentFrame = 0;
float frameRate = 0.1f;
float frameTimer = 0.0f;
bool isKeyPressed = false;

Rectangle runRightFrames[] = {
        {0, 0, 66, 95},
        {73, 0, 66, 95},
        {146, 0, 66, 95}
};
Rectangle runLeftFrames[] = {
        {0, 104, 66, 95},
        {73, 104, 66, 95},
        {146, 104, 66, 95}
};

Rectangle good[] = {
        {0, 0, 44, 50},
        {44, 0, 45, 50},
        {89, 0, 46, 50},
        {132, 0, 44, 50},
        {177, 0, 49, 50},
};

Rectangle bad[] = {
        {0, 0, 49, 50},
        {49, 0, 50, 50},
        {99, 0, 49, 50},
        {148, 0, 50, 50},
};

const Rectangle *currentFrames = runRightFrames;
Texture2D background, playerTexture, badTexture, goodTexture;
Sound bonus, lostBonus, damage, mainTheme, speaking1, speaking2;

int score = 0;
int fruitsCaught = 0;
float veryGoodFruitTimer = 0.0f;

int randomGoodIndex = GetRandomValue(0, 3);
int randomBadIndex = GetRandomValue(0, 2);

const char* text1 = "Now you need to prepare for the session and colloquia.\n\n"
                    "Use buttons A and D to move around.\n\n"
                    "You can also move quickly from one side of the screen to the other.";

const char* text2 = "The main thing to remember is to stay focused on your preparation or you\nwon't be able to pass the tests.\n\n"
                    "Sometimes you'll want to cut down the information through chat gpt.\n\n"
                    "You should not do that.";

int textLength1 = strlen(text1);
int currentLength1 = 0;
int framesCounter1 = 0;

int textLength2 = strlen(text2);
int currentLength2 = 0;
int framesCounter2 = 0;

float letterDelay = 1;


bool DialogueWindow1 = true;
bool DialogueWindow2 = false;
bool isRightHalf = false;

Rectangle player = { static_cast<float>(screenWidth / 2), 807, 70, 90 };
Rectangle goodFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
Rectangle badFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
Rectangle veryGoodFruit = { -40, -40, 40, 40 };
Rectangle veryBadFruit = { -40, -40, 40, 40 };

#endif CATCH_H