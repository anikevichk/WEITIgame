#include "raylib.h"
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
    Rectangle *currentFrames = runRightFrames;

    Texture2D playerTexture = LoadTexture("../src/sprite.png");

    Rectangle player = { static_cast<float>(screenWidth / 2), 807, 70, 90 };
    Rectangle goodFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle badFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle veryGoodFruit = { -40, -40, 40, 40 };
    Rectangle veryBadFruit = { -40, -40, 40, 40 };

    int score = 0;
    int fruitsCaught = 0;
    float veryGoodFruitTimer = 0.0f;
    float veryGoodFruitInterval = 15.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        veryGoodFruitTimer += deltaTime;

        Rectangle previousPosition = player;

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
            score++;
            fruitsCaught++;
            goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            goodFruit.y = 0;
        }

        if (CheckCollisionRecs(player, veryGoodFruit)) {
            score += 3;
            fruitsCaught++;
            veryGoodFruit.x = -40;
            veryGoodFruit.y = -40;
        }

        if (CheckCollisionRecs(player, badFruit)) {
            score--;
            badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            badFruit.y = 0;
        }

        if (veryBadFruit.y > -40 && CheckCollisionRecs(player, veryBadFruit)) {
            window.setScreen(Window::LOSS);
            break;
        }

        if (goodFruit.y > screenHeight) {
            score--;
            goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            goodFruit.y = 0;
        }

        // Check for bad fruits falling to the floor
        if (badFruit.y > screenHeight) {
            badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            badFruit.y = 0;
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

        // Draw the player and fruits
        DrawTextureRec(playerTexture, currentFrames[currentFrame], (Vector2){ player.x, player.y }, WHITE);
        DrawRectangleRec(goodFruit, GREEN);
        DrawRectangleRec(badFruit, RED);
        DrawRectangleRec(veryGoodFruit, YELLOW);
        DrawRectangleRec(veryBadFruit, BLACK);

        // Draw text with the score
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        // Draw the fruit collection bar
        float barLength = static_cast<float>(screenWidth / 2);
        float barWidth = (barLength * score        ) / maxFruits;

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

        EndDrawing();
    }
}

