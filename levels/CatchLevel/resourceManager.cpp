#include "resourceManager.h"
#include "../../Tools/DrawTools.h"

// Load game resources
void resourceManager::LoadGameResources(Texture2D& backgroundTex, Texture2D& playerTex, Texture2D& badTex, Texture2D& goodTex,
                                        Sound& bonusSnd, Sound& lostBonusSnd, Sound& damageSnd, Sound& mainThemeSnd, Sound& speaking1,Sound& speaking2 ) {
    // Load textures
    backgroundTex = LoadTexture("../src/levelCatch/background.png");
    playerTex = LoadTexture("../src/sprite.png");
    badTex = LoadTexture("../src/levelCatch/bad.png");
    goodTex = LoadTexture("../src/levelCatch/good.png");

    // Load sounds
    speaking1 = LoadSound("../src/sounds/voice2.mp3");
    speaking2 = LoadSound("../src/sounds/voice1.mp3");
    bonusSnd = LoadSound("../src/sounds/bonus.mp3");
    lostBonusSnd = LoadSound("../src/sounds/lostBonus.mp3");
    damageSnd = LoadSound("../src/sounds/damage.mp3");
    mainThemeSnd = LoadSound("../src/sounds/CatchMainTheme.mp3");

    // Set sound volumes
    SetSoundVolume(speaking1, 0.5);
    SetSoundVolume(speaking2, 0.5);
    SetSoundVolume(damageSnd, 0.4);
    SetSoundVolume(lostBonusSnd, 0.8);
    SetSoundVolume(bonusSnd, 0.8);
}

// Unload game resources
void resourceManager::UnloadGameResources(Texture2D& backgroundTex, Texture2D& playerTex, Texture2D& badTex, Texture2D& goodTex,
                                          Sound& bonusSnd, Sound& lostBonusSnd, Sound& damageSnd, Sound& mainThemeSnd, Sound& speaking1,Sound& speaking2) {
    // Unload textures
    UnloadTexture(backgroundTex);
    UnloadTexture(playerTex);
    UnloadTexture(goodTex);
    UnloadTexture(badTex);
//    unloadTeachers();

    // Stop and unload sounds
    StopSound(mainThemeSnd);
    UnloadSound(speaking1);
    UnloadSound(speaking2);
    UnloadSound(bonusSnd);
    UnloadSound(lostBonusSnd);
    UnloadSound(damageSnd);
    UnloadSound(mainThemeSnd);
}

// Update player movement
void resourceManager::UpdatePlayer(Rectangle& player, bool& isKeyPressed, const Rectangle* &currentFrames, const Rectangle runRightFrames[], const Rectangle runLeftFrames[]) {
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

    // Wrap player around screen edges
    if (player.x < 0) {
        player.x = GetScreenWidth();
    }
    if (player.x > GetScreenWidth()) {
        player.x = 0;
    }
}
