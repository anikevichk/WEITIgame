#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "raylib.h"

class resourceManager {
public:
    static void LoadGameResources(Texture2D& backgroundTex, Texture2D& playerTex, Texture2D& badTex, Texture2D& goodTex,
                                  Sound& bonusSnd, Sound& lostBonusSnd, Sound& damageSnd, Sound& mainThemeSnd, Sound& speaking1,Sound& speaking2);

    static void UnloadGameResources(Texture2D& backgroundTex, Texture2D& playerTex, Texture2D& badTex, Texture2D& goodTex,
                                    Sound& bonusSnd, Sound& lostBonusSnd, Sound& damageSnd, Sound& mainThemeSnd, Sound& speaking1,Sound& speaking2);

    static void UpdatePlayer(Rectangle& player, bool& isKeyPressed, const Rectangle* &currentFrames, const Rectangle runRightFrames[], const Rectangle runLeftFrames[]);
};

#endif // RESOURCEMANAGER_H