#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "raylib.h"

class ResourceManager {
public:
    static void LoadResources(Texture2D& hotdog, Texture2D& wallH, Texture2D& wallV, Texture2D& sprite, Texture2D& background, Sound& mainTheme, Sound& bonus);
    static void UnloadResources(Texture2D& hotdog, Texture2D& wallH, Texture2D& wallV, Texture2D& background, Sound& mainTheme, Sound& bonus);
    static void HandlePlayerMovement(Rectangle& player, Vector2& direction, Rectangle*& currentFrames, bool& isKeyPressed, float speed,
                                     Rectangle runForwardFrames[], Rectangle runBackFrames[], Rectangle runLeftFrames[], Rectangle runRightFrames[]);
};

#endif // RESOURCEMANAGER_H
