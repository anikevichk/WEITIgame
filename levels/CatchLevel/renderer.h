#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"

class render{
public:
    static void DrawGameObjects(Texture2D background, Texture2D playerTexture, Texture2D goodTexture, Texture2D badTexture,
                                const Rectangle* currentFrames, int currentFrame, int randomGoodIndex, int randomBadIndex,
                                Rectangle player, Rectangle goodFruit, Rectangle badFruit, Rectangle veryGoodFruit, Rectangle veryBadFruit,
                                int score, float barLength, float barWidth, const Rectangle* good, const Rectangle* bad);
};

#endif // RENDER_H