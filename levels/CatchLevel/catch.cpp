#include "raylib.h"
#include "../../Scenes/scenes.h"
#include "renderer.h"
#include "collision.h"
#include "resourceManager.h"

void Catch(Window &window) {
    int screenWidth = 1600;
    int screenHeight = 900;
    int maxFruits = 20;

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

    const Rectangle *currentFrames = runRightFrames;
    Texture2D background, playerTexture, badTexture, goodTexture;
    Sound bonus, lostBonus, damage, mainTheme;

    resourceManager::LoadGameResources(background, playerTexture, badTexture, goodTexture, bonus, lostBonus, damage, mainTheme);

    Rectangle player = { static_cast<float>(screenWidth / 2), 807, 70, 90 };
    Rectangle goodFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle badFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle veryGoodFruit = { -40, -40, 40, 40 };
    Rectangle veryBadFruit = { -40, -40, 40, 40 };

    int score = 0;
    int fruitsCaught = 0;
    float veryGoodFruitTimer = 0.0f;


    int randomGoodIndex = GetRandomValue(0,3);
    int randomBadIndex = GetRandomValue(0,2);

    SetTargetFPS(60);
    PlaySound(mainTheme);

    while (!WindowShouldClose()) {

        if (!IsSoundPlaying(mainTheme)) {
            PlaySound(mainTheme);
        }

        float deltaTime = GetFrameTime();
        veryGoodFruitTimer += deltaTime;

        resourceManager::UpdatePlayer(player, isKeyPressed, currentFrames, runRightFrames, runLeftFrames);

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

        goodFruit.y += 5;
        badFruit.y += 6;

        float barLength = static_cast<float>(screenWidth / 2);
        float barWidth = (barLength * score) / maxFruits;

        collision::CheckCollisions(player, goodFruit, badFruit, veryGoodFruit, veryBadFruit, score,
                                   fruitsCaught, bonus, lostBonus, damage, screenWidth, screenHeight,
                                   window, randomGoodIndex, randomBadIndex, veryGoodFruitTimer);



        BeginDrawing();

        render::DrawGameObjects(background, playerTexture, goodTexture, badTexture, currentFrames, currentFrame, randomGoodIndex, randomBadIndex,
                        player, goodFruit, badFruit, veryGoodFruit, veryBadFruit, score, barLength, barWidth, good, bad);


        if (score >= maxFruits) {
            window.setScreen(Window::VICTORY);
            break;
        }

        if (score < 0) {
            window.setScreen(Window::LOSS);
            break;
        }

        EndDrawing();
    }
    resourceManager::UnloadGameResources(background, playerTexture, goodTexture, badTexture, bonus, lostBonus, damage, mainTheme);
}
