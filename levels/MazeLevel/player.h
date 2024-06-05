#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "cell.h"

class Player {
public:
    static void UpdateAndCheckCollisions(Rectangle& player, const Vector2& direction,
                                         std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight,
                                         std::vector<Rectangle>& hotdogs, int& collectedHotdogs, bool& gameWon,
                                         Rectangle& previousPosition, Sound& bonus);
    static void UpdateAndDrawAnimation(Rectangle& player, Rectangle currentFrames[], int& currentFrame,
                                       bool isKeyPressed, Texture2D& sprite, float scale);
};

#endif // PLAYER_H