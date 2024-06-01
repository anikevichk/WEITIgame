#include "raylib.h"
#include "../../Scenes/scenes.h"
#include <vector>
#include "player.h"
#include "resourceManager.h"
#include "renderer.h"
#include "mazeGenerator.h"
#include "../../Tools/DrawTools.h"
#include <cstring>

void Maze(Window &window) {

    Texture2D hotdog, wallH, wallV, sprite, background;
    Sound mainTheme, bonus, speaking1, speaking2;

    // Load resources
    ResourceManager::LoadResources(hotdog, wallH, wallV, sprite, background, mainTheme, bonus, speaking1, speaking2);

    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 5.0f;
    SetTargetFPS(60);
    PlaySound(mainTheme);

    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;
    bool DialogueWindow = true;

    float scale = 0.8f;

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
    Rectangle runBackFrames[] = {
            {0,   208, 73, 95},
            {75,  208, 73, 95},
            {158, 208, 73, 95}
    };
    Rectangle runForwardFrames[] = {
            {0,   312, 73, 95},
            {75,  312, 73, 95},
            {158, 312, 73, 95}
    };
    Rectangle *currentFrames = runRightFrames;

    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    Rectangle player = {15, 807, 70.0f * scale, 90.0f * scale};

    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));

    // Generate maze
    MazeGenerator::Generate(maze, mazeWidth, mazeHeight);


    std::vector<Rectangle> hotdogs;
    MazeGenerator::GenerateHotdogs(hotdogs, maze, mazeWidth, mazeHeight, 5);

    int collectedHotdogs = 0;
    bool gameWon = false;
    const char* text1 = "It's your first day at WEITI. Try to find the right classroom.";
    const char* text2 = "You need to get all the hotdogs to get into the classroom.\n\nUse the keys A, S, D, W to move around.";

    int textLength1 = strlen(text1);
    int currentLength1 = 0;
    int framesCounter1 = 0;

    int textLength2 = strlen(text2);
    int currentLength2 = 0;
    int framesCounter2 = 0;

    float letterDelay = 1;


    bool DialogueWindow1 = true;
    bool DialogueWindow2 = false;
    bool isRightHalf = true;

    SetSoundVolume(mainTheme, 0.3);

    HandleDialogueWindow(text1, currentLength1, textLength1, framesCounter1, speaking2,
                         background, letterDelay, DialogueWindow1, isRightHalf);
    if (!DialogueWindow1) {
        DialogueWindow2 = true;
        isRightHalf = false;
    }

    HandleDialogueWindow(text2, currentLength2, textLength2, framesCounter2, speaking1,
                         background, letterDelay, DialogueWindow2, isRightHalf);
    SetSoundVolume(mainTheme, 0.7);

    while (!WindowShouldClose()) {
        if (!IsSoundPlaying(mainTheme)) {
            PlaySound(mainTheme);
        }

        Vector2 direction = {0, 0};

        Rectangle previousPosition = player;

        ResourceManager::HandlePlayerMovement(player, direction, currentFrames, isKeyPressed, speed, runForwardFrames, runBackFrames, runLeftFrames, runRightFrames);

        // Update player position and check collisions
        Player::UpdateAndCheckCollisions(player, direction, maze, mazeWidth, mazeHeight, hotdogs, collectedHotdogs, gameWon, previousPosition, bonus);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        Player::UpdateAndDrawAnimation(player, currentFrames, currentFrame, isKeyPressed, sprite, scale);
        Renderer::DrawMazeWalls(maze, mazeWidth, mazeHeight, wallH, wallV);
        Renderer::DrawHotdogsAndCollectedText(hotdogs, collectedHotdogs, hotdog);

        if (gameWon) {
            window.setScreen(Window::VICTORY);
            break;
        }

        EndDrawing();
    }

    ResourceManager::UnloadResources(hotdog, wallH, wallV, background, mainTheme, bonus, speaking1, speaking2);
}
