#include "raylib.h"
#include "../../Scenes/scenes.h"
#include "renderer.h"
#include "collision.h"
#include "resourceManager.h"
#include "../../Tools/DrawTools.h"
#include <cstring>

// Function to handle the "Catch" mini-game
void Catch(Window &window) {
    // Screen dimensions
    int screenWidth = 1600;
    int screenHeight = 900;

    // Maximum number of fruits
    int maxFruits = 20;

    // Variables related to animation
    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;

    // Animation frames for player movement
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

    // Frames for good and bad fruits
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

    // Pointer to current animation frames
    const Rectangle *currentFrames = runRightFrames;

    // Textures and sounds
    Texture2D background, playerTexture, badTexture, goodTexture;
    Sound bonus, lostBonus, damage, mainTheme, speaking1, speaking2;

    // Game state variables
    int score = 0;
    int fruitsCaught = 0;
    float veryGoodFruitTimer = 0.0f;

    // Random indices for good and bad fruits
    int randomGoodIndex = GetRandomValue(0, 3);
    int randomBadIndex = GetRandomValue(0, 2);

    // Text for dialogue windows
    const char* text1 = "Now you need to prepare for the session and colloquia.\n\n"
                        "Use buttons A and D to move around.\n\n"
                        "You can also move quickly from one side of the screen to the other.";
    const char* text2 = "The main thing to remember is to stay focused on your preparation.\n\n"
                        "Sometimes you'll want to cut down the information through chat gpt.\n\n"
                        "You should not do that.";

    // Length of text for dialogue windows
    int textLength1 = strlen(text1);
    int currentLength1 = 0;
    int framesCounter1 = 0;
    int textLength2 = strlen(text2);
    int currentLength2 = 0;
    int framesCounter2 = 0;

    // Delay for displaying letters in dialogue windows
    float letterDelay = 1;

    // Flags for controlling dialogue windows
    bool DialogueWindow1 = true;
    bool DialogueWindow2 = false;
    bool isRightHalf = false;

    // Initial positions of player and fruits
    Rectangle player = { static_cast<float>(screenWidth / 2), 807, 70, 90 };
    Rectangle goodFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle badFruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };
    Rectangle veryGoodFruit = { -40, -40, 40, 40 };
    Rectangle veryBadFruit = { -40, -40, 40, 40 };

    // Load game resources
    resourceManager::LoadGameResources(background, playerTexture, badTexture, goodTexture, bonus,
                                       lostBonus, damage, mainTheme, speaking1, speaking2);

    // Set up frame rate and play main theme
    SetTargetFPS(60);
    PlaySound(mainTheme);
    SetSoundVolume(mainTheme, 0.3);

    // Handle dialogue window
    HandleDialogueWindow(text1, currentLength1, textLength1, framesCounter1, speaking1,
                         background, letterDelay, DialogueWindow1, isRightHalf);
    if (!DialogueWindow1) {
        DialogueWindow2 = true;
        isRightHalf = true;
    }

    // Continue handling dialogue
    HandleDialogueWindow(text2, currentLength2, textLength2, framesCounter2, speaking2,
                         background, letterDelay, DialogueWindow2, isRightHalf);
    SetSoundVolume(mainTheme, 0.7);

    // Main game loop
    while (!WindowShouldClose()) {
        // Ensure main theme is playing
        if (!IsSoundPlaying(mainTheme)) {
            PlaySound(mainTheme);
        }

        float deltaTime = GetFrameTime();
        veryGoodFruitTimer += deltaTime;

        // Update player movement
        resourceManager::UpdatePlayer(player, isKeyPressed, currentFrames, runRightFrames, runLeftFrames);

        // Update animation frames
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

        // Update fruit positions
        goodFruit.y += 7;
        badFruit.y += 6;

        // Calculate progress bar length
        float barLength = static_cast<float>(screenWidth / 2);
        float barWidth = (barLength * score) / maxFruits;

        // Check for collisions and update game state
        collision::CheckCollisions(player, goodFruit, badFruit, veryGoodFruit, veryBadFruit, score,
                                   fruitsCaught, bonus, lostBonus, damage, screenWidth, screenHeight,
                                   window, randomGoodIndex, randomBadIndex, veryGoodFruitTimer);

        // Check collision with veryBadFruit
        if (veryBadFruit.y > -40 && CheckCollisionRecs(player, veryBadFruit)) {
            window.setScreen(Window::LOSS);
            break;
        }

        // Begin drawing game objects
        BeginDrawing();
        render::DrawGameObjects(background, playerTexture, goodTexture, badTexture, currentFrames, currentFrame,
                                randomGoodIndex, randomBadIndex, player, goodFruit, badFruit, veryGoodFruit,
                                veryBadFruit, score, barLength, barWidth, good, bad);

        // Check for victory or loss conditions
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

    // Unload game resources
    resourceManager::UnloadGameResources(background, playerTexture, goodTexture, badTexture, bonus,
                                         lostBonus, damage, mainTheme, speaking1, speaking2);
}
