#include "raylib.h"
#include "../../Scenes/scenes.h"
#include <vector>
#include "player.h"
#include "resourceManager.h"
#include "renderer.h"
#include "mazeGenerator.h"
#include "../../Tools/DrawTools.h"
#include <cstring>

// Function for Maze Scene
void Maze(Window &window) {

    // Initialization and loading necessary textures and sounds
    Texture2D hotdog, wallH, wallV, sprite, background;
    Sound mainTheme, bonus, speaking1, speaking2;
    ResourceManager::LoadResources(hotdog, wallH, wallV, sprite, background, mainTheme, bonus, speaking1, speaking2);

    // Setting up screen dimensions and speed
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 5.0f;
    SetTargetFPS(60);
    PlaySound(mainTheme);

    // Setting up variables for animation
    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;

    // Setting up scale for textures
    float scale = 0.8f;

    // Arrays containing frame rectangles for animation
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

    // Calculating maze dimensions based on screen size
    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    // Rectangle representing player
    Rectangle player = {15, 807, 70.0f * scale, 90.0f * scale};

    // Variables for dialogue text and window control
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


    // Generating maze
    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));

    MazeGenerator::Generate(maze, mazeWidth, mazeHeight);

    // Generating hotdogs
    std::vector<Rectangle> hotdogs;
    MazeGenerator::GenerateHotdogs(hotdogs, maze, mazeWidth, mazeHeight, 5);

    // Setting sound volume and handling dialogue windows
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

    // Main game loop
    while (!WindowShouldClose()) {
        if (!IsSoundPlaying(mainTheme)) {
            PlaySound(mainTheme);
        }

        // Handling player movement
        Vector2 direction = {0, 0};
        Rectangle previousPosition = player;
        ResourceManager::HandlePlayerMovement(player, direction, currentFrames, isKeyPressed, speed, runForwardFrames, runBackFrames, runLeftFrames, runRightFrames);
        Player::UpdateAndCheckCollisions(player, direction, maze, mazeWidth, mazeHeight, hotdogs, collectedHotdogs, gameWon, previousPosition, bonus);

        // Drawing game elements
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        Player::UpdateAndDrawAnimation(player, currentFrames, currentFrame, isKeyPressed, sprite, scale);
        Renderer::DrawMazeWalls(maze, mazeWidth, mazeHeight, wallH, wallV);
        Renderer::DrawHotdogsAndCollectedText(hotdogs, collectedHotdogs, hotdog);

        // Check for game win condition
        if (gameWon) {
            window.setScreen(Window::VICTORY);
            break;
        }

        EndDrawing();
    }

    // Unloading resources
    ResourceManager::UnloadResources(hotdog, wallH, wallV, background, mainTheme, bonus, speaking1, speaking2);
}
