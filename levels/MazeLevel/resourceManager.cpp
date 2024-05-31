#include "resourceManager.h"

void ResourceManager::LoadResources(Texture2D& hotdog, Texture2D& wallH, Texture2D& wallV, Texture2D& sprite, Texture2D& background, Sound& mainTheme, Sound& bonus) {
    hotdog = LoadTexture("../src/hotdog.png");
    wallH = LoadTexture("../src/levelMaze/wallH.png");
    wallV = LoadTexture("../src/levelMaze/wallV.png");
    sprite = LoadTexture("../src/sprite.png");
    background = LoadTexture("../src/levelMaze/background.png");

    mainTheme = LoadSound("../src/sounds/MazeMainTheme.mp3");
    bonus = LoadSound("../src/sounds/bonus.wav");
    SetSoundVolume(bonus, 0.3);
}

void ResourceManager::UnloadResources(Texture2D& hotdog, Texture2D& wallH, Texture2D& wallV, Texture2D& background, Sound& mainTheme, Sound& bonus) {
    UnloadTexture(hotdog);
    UnloadTexture(wallH);
    UnloadTexture(wallV);
    UnloadTexture(background);

    StopSound(mainTheme);
    UnloadSound(mainTheme);
    UnloadSound(bonus);
}

void ResourceManager::HandlePlayerMovement(Rectangle& player, Vector2& direction, Rectangle*& currentFrames, bool& isKeyPressed, float speed,
                          Rectangle runForwardFrames[], Rectangle runBackFrames[], Rectangle runLeftFrames[], Rectangle runRightFrames[]) {
    if (IsKeyDown(KEY_W)) {
        direction = {0, -speed};
        currentFrames = runForwardFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_S)) {
        direction = {0, speed};
        currentFrames = runBackFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_A)) {
        direction = {-speed, 0};
        currentFrames = runLeftFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_D)) {
        direction = {speed, 0};
        currentFrames = runRightFrames;
        isKeyPressed = true;
    } else {
        isKeyPressed = false;
    }
}