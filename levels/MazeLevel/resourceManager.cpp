#include "resourceManager.h"
#include "../../Tools/DrawTools.h"

// Load all game resources
void ResourceManager::LoadResources(Texture2D& hotdog, Texture2D& wallH, Texture2D& wallV, Texture2D& sprite,
                                    Texture2D& background, Sound& mainTheme, Sound& bonus, Sound& speaking1,
                                    Sound& speaking2) {
    // Load textures
    hotdog = LoadTexture("../src/hotdog.png");
    wallH = LoadTexture("../src/levelMaze/wallH.png");
    wallV = LoadTexture("../src/levelMaze/wallV.png");
    sprite = LoadTexture("../src/sprite.png");
    background = LoadTexture("../src/levelMaze/background.png");

    // Load sounds and set volume
    speaking1 = LoadSound("../src/sounds/voice2.mp3");
    speaking2 = LoadSound("../src/sounds/voice1.mp3");
    mainTheme = LoadSound("../src/sounds/MazeMainTheme.mp3");
    bonus = LoadSound("../src/sounds/bonus.wav");
    SetSoundVolume(speaking1, 0.5);
    SetSoundVolume(speaking2, 0.5);
    SetSoundVolume(bonus, 0.3);
}

// Unload all game resources
void ResourceManager::UnloadResources(Texture2D& hotdog, Texture2D& wallH, Texture2D& wallV, Texture2D& background,
                                      Sound& mainTheme, Sound& bonus, Sound& speaking1, Sound& speaking2) {
    // Unload textures
    UnloadTexture(hotdog);
    UnloadTexture(wallH);
    UnloadTexture(wallV);
    UnloadTexture(background);
    unloadTeachers();

    // Stop and unload sounds
    StopSound(mainTheme);
    UnloadSound(speaking1);
    UnloadSound(speaking2);
    UnloadSound(mainTheme);
    UnloadSound(bonus);
}

// Handle player movement based on keyboard input
void ResourceManager::HandlePlayerMovement(Rectangle& player, Vector2& direction, Rectangle*& currentFrames,
                                           bool& isKeyPressed, float speed,Rectangle runForwardFrames[],
                                           Rectangle runBackFrames[], Rectangle runLeftFrames[],
                                           Rectangle runRightFrames[]) {
    // Check keyboard input for movement direction
    if (IsKeyDown(KEY_W)) {
        direction = {0, -speed}; // Move up
        currentFrames = runForwardFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_S)) {
        direction = {0, speed}; // Move down
        currentFrames = runBackFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_A)) {
        direction = {-speed, 0}; // Move left
        currentFrames = runLeftFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_D)) {
        direction = {speed, 0}; // Move right
        currentFrames = runRightFrames;
        isKeyPressed = true;
    } else {
        isKeyPressed = false;
    }
}
