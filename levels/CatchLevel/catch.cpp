#include "raylib.h"
#include "../../Scenes/scenes.h"
#include "renderer.h"
#include "collision.h"
#include "resourceManager.h"
#include "../../Tools/DrawTools.h"
#include <cstring>
#include "catch.h"

void Catch(Window &window) {

    resourceManager::LoadGameResources(background, playerTexture, badTexture, goodTexture, bonus,
                                       lostBonus, damage, mainTheme, speaking1, speaking2);

    SetTargetFPS(60);
    PlaySound(mainTheme);
    SetSoundVolume(mainTheme, 0.3);

    HandleDialogueWindow(text1, currentLength1, textLength1, framesCounter1, speaking1,
                         background, letterDelay, DialogueWindow1, isRightHalf);
    if (!DialogueWindow1) {
        DialogueWindow2 = true;
        isRightHalf = true;
    }

    HandleDialogueWindow(text2, currentLength2, textLength2, framesCounter2, speaking2,
                         background, letterDelay, DialogueWindow2, isRightHalf);
    StopSound(speaking2);
    SetSoundVolume(mainTheme, 0.7);

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
        render::DrawGameObjects(background, playerTexture, goodTexture, badTexture, currentFrames, currentFrame,
                                randomGoodIndex, randomBadIndex, player, goodFruit, badFruit, veryGoodFruit,
                                veryBadFruit, score, barLength, barWidth, good, bad);

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
    resourceManager::UnloadGameResources(background, playerTexture, goodTexture, badTexture, bonus,
                                         lostBonus, damage, mainTheme, speaking1, speaking2);
}
