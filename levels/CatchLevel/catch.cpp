#include "raylib.h"
#include <random>
#include "../../Scenes/scenes.h"

void Catch(Window &window) {
    const int screenWidth = 1600;
    const int screenHeight = 900;
    const int maxFruits = 20;

    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;

    Rectangle runRightFrames[] = {
            {0,   0, 66, 95},
            {73,  0, 66, 95},
            {146, 0, 66, 95}
    };
    Rectangle runLeftFrames[] = {
            {0,   104, 66, 95},
            {73,  104, 66, 95},
            {146, 104, 66, 95}
    };

    Rectangle good[] = {
            {0,   0, 44, 50},
            {44,   0, 45, 50},
            {89,   0, 46, 50},
            {132,   0, 44, 50},
            {177,   0, 49, 50},
    };

    Rectangle bad[] = {
            {0,   0, 49, 50},
            {49,   0, 50, 50},
            {99,   0, 49, 50},
            {148,   0, 50, 50},
    };

    Rectangle *currentFrames = runRightFrames;

    Texture2D background = LoadTexture("../src/levelCatch/background.png");
    Texture2D playerTexture = LoadTexture("../src/sprite.png");
    Texture2D badTexture = LoadTexture("../src/levelCatch/bad.png");
    Texture2D goodTexture = LoadTexture("../src/levelCatch/good.png");

    Sound bonus = LoadSound("../src/sounds/bonus.mp3");
    SetSoundVolume(bonus, 1);

    Rectangle player = { static_cast<float>(screenWidth / 2), 807, 70, 90 };
    Rectangle goodFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle badFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle veryGoodFruit = { -40, -40, 40, 40 };
    Rectangle veryBadFruit = { -40, -40, 40, 40 };

    int score = 0;
    int fruitsCaught = 0;
    float veryGoodFruitTimer = 0.0f;
    float veryGoodFruitInterval = 15.0f;

    int randomGoodIndex = GetRandomValue(0,3);
    int randomBadIndex = GetRandomValue(0,2);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        veryGoodFruitTimer += deltaTime;

        // Check player input for movement
        if (IsKeyDown(KEY_A)) {
            player.x -= 7;
            currentFrames = runLeftFrames;
            isKeyPressed = true;
        } else if (IsKeyDown(KEY_D)) {
            player.x += 7;
            currentFrames = runRightFrames;
            isKeyPressed = true;
        } else {
            isKeyPressed = false;
        }

        frameTimer += GetFrameTime();
        if (frameTimer >= frameRate) {
            frameTimer = 0.0f;
            if (isKeyPressed) {
                currentFrame++;
                if (currentFrame >= 3) {
                    currentFrame = 0;
                }
            } else {
                currentFrame = 0;
            }
        }

        if (player.x < 0) {
            player.x = screenWidth;
        }
        if (player.x > screenWidth) {
            player.x = 0;
        }

        goodFruit.y += 5;
        badFruit.y += 6;

        if (veryGoodFruit.y > -40) {
            veryGoodFruit.y += 4;
        }
        if (veryBadFruit.y > -40) {
            veryBadFruit.y += 7;
        };



        if (CheckCollisionRecs(player, goodFruit)) {
            PlaySound(bonus);
            score++;
            fruitsCaught++;
            goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            goodFruit.y = 0;
            randomGoodIndex = GetRandomValue(0,3);
        }

        if (CheckCollisionRecs(player, veryGoodFruit)) {
            score += 3;
            fruitsCaught++;
            veryGoodFruit.x = -40;
            veryGoodFruit.y = -40;
            PlaySound(bonus);
        }

        if (CheckCollisionRecs(player, badFruit)) {
            score--;
            badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            badFruit.y = 0;
            randomBadIndex = GetRandomValue(0,2);
        }

        if (veryBadFruit.y > -40 && CheckCollisionRecs(player, veryBadFruit)) {
            window.setScreen(Window::LOSS);
            break;
        }

        if (goodFruit.y > screenHeight) {
            score--;
            goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            goodFruit.y = 0;
            randomGoodIndex = GetRandomValue(0,3);
        }

        // Check for bad fruits falling to the floor
        if (badFruit.y > screenHeight) {
            badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            badFruit.y = 0;
            randomBadIndex = GetRandomValue(0,2);
        }

        // Check for very good fruits falling to the floor
        if (veryGoodFruit.y > screenHeight) {
            score--;
            veryGoodFruit.x = -40;
            veryGoodFruit.y = -40;
        }

        // Check for very bad fruits falling to the floor
        if (veryBadFruit.y > screenHeight) {
            veryBadFruit.x = -40;
            veryBadFruit.y = -40;
        }

        // Timer for spawning very good fruit every 15 seconds
        if (veryGoodFruitTimer >= veryGoodFruitInterval) {
            veryGoodFruitTimer = 0.0f;
            veryGoodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            veryGoodFruit.y = 0;
        }

        // Spawn a very bad fruit every fifth caught fruit
        if (fruitsCaught > 0 && fruitsCaught % 5 == 0) {
            fruitsCaught = 0;
            veryBadFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            veryBadFruit.y = 0;
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

//
        // Draw the player and fruits
        DrawTextureRec(playerTexture, currentFrames[currentFrame], (Vector2){ player.x, player.y }, WHITE);
        DrawTextureRec(goodTexture, good[randomGoodIndex], (Vector2){ goodFruit.x, goodFruit.y }, WHITE);
        DrawTextureRec(badTexture, bad[randomBadIndex], (Vector2){ badFruit.x, badFruit.y }, WHITE);
        DrawTextureRec(goodTexture, good[4], (Vector2){ veryGoodFruit.x, veryGoodFruit.y }, WHITE);
        DrawTextureRec(badTexture, bad[3], (Vector2){ veryBadFruit.x, veryBadFruit.y }, WHITE);

        // Draw text with the score
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        // Draw the fruit collection bar
        float barLength = static_cast<float>(screenWidth / 2);
        float barWidth = (barLength * score) / maxFruits;

        DrawRectangleLines(10, 50, static_cast<int>(barLength), 20, BLACK);
        DrawRectangle(10, 50, static_cast<int>(barWidth), 20, GREEN);

        // Check for victory condition
        if (score >= maxFruits) {
            window.setScreen(Window::VICTORY);
            break;
        }

        // Check for loss condition
        if (score < 0) {
            window.setScreen(Window::LOSS);
            break;
        }

        UnloadSound(bonus);

        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(playerTexture);
    UnloadTexture(goodTexture);
    UnloadTexture(badTexture);

}

