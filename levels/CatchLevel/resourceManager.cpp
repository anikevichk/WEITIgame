#include "resourceManager.h"
#include "../../Tools/DrawTools.h"

void resourceManager::LoadGameResources(Texture2D& backgroundTex, Texture2D& playerTex, Texture2D& badTex, Texture2D& goodTex,
                                        Sound& bonusSnd, Sound& lostBonusSnd, Sound& damageSnd, Sound& mainThemeSnd, Sound& speaking1,Sound& speaking2 ) {
    backgroundTex = LoadTexture("../src/levelCatch/background.png");
    playerTex = LoadTexture("../src/sprite.png");
    badTex = LoadTexture("../src/levelCatch/bad.png");
    goodTex = LoadTexture("../src/levelCatch/good.png");

    speaking1 = LoadSound("../src/sounds/voice2.mp3");
    speaking2 = LoadSound("../src/sounds/voice1.mp3");
    bonusSnd = LoadSound("../src/sounds/bonus.mp3");
    lostBonusSnd = LoadSound("../src/sounds/lostBonus.mp3");
    damageSnd = LoadSound("../src/sounds/damage.mp3");
    mainThemeSnd = LoadSound("../src/sounds/CatchMainTheme.mp3");
    SetSoundVolume(damageSnd, 0.4);
    SetSoundVolume(lostBonusSnd, 0.8);
    SetSoundVolume(bonusSnd, 0.8);
}

void resourceManager::UnloadGameResources(Texture2D& backgroundTex, Texture2D& playerTex, Texture2D& badTex, Texture2D& goodTex,
                                          Sound& bonusSnd, Sound& lostBonusSnd, Sound& damageSnd, Sound& mainThemeSnd, Sound& speaking1,Sound& speaking2) {
    UnloadTexture(backgroundTex);
    UnloadTexture(playerTex);
    UnloadTexture(goodTex);
    UnloadTexture(badTex);
    unloadTeachers();

    StopSound(mainThemeSnd);
    UnloadSound(speaking1);
    UnloadSound(speaking2);
    UnloadSound(bonusSnd);
    UnloadSound(lostBonusSnd);
    UnloadSound(damageSnd);
    UnloadSound(mainThemeSnd);
}

void resourceManager::UpdatePlayer(Rectangle& player, bool& isKeyPressed, const Rectangle* &currentFrames, const Rectangle runRightFrames[], const Rectangle runLeftFrames[]) {
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

    if (player.x < 0) {
        player.x = GetScreenWidth();
    }
    if (player.x > GetScreenWidth()) {
        player.x = 0;
    }
}