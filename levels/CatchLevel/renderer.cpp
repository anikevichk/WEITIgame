#include "renderer.h"

void render::DrawGameObjects(Texture2D background, Texture2D playerTexture, Texture2D goodTexture, Texture2D badTexture,
                             const Rectangle* currentFrames, int currentFrame, int randomGoodIndex, int randomBadIndex,
                             Rectangle player, Rectangle goodFruit, Rectangle badFruit, Rectangle veryGoodFruit, Rectangle veryBadFruit,
                             int score, float barLength, float barWidth, const Rectangle* good, const Rectangle* bad) {
    ClearBackground(RAYWHITE);

    DrawTexture(background, 0, 0, WHITE);

    DrawTextureRec(playerTexture, currentFrames[currentFrame], (Vector2){ player.x, player.y }, WHITE);
    DrawTextureRec(goodTexture, good[randomGoodIndex], (Vector2){ goodFruit.x, goodFruit.y }, WHITE);
    DrawTextureRec(badTexture, bad[randomBadIndex], (Vector2){ badFruit.x, badFruit.y }, WHITE);
    DrawTextureRec(goodTexture, good[4], (Vector2){ veryGoodFruit.x, veryGoodFruit.y }, WHITE);
    DrawTextureRec(badTexture, bad[3], (Vector2){ veryBadFruit.x, veryBadFruit.y }, WHITE);

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

    DrawRectangleLines(10, 50, static_cast<int>(barLength), 20, BLACK);
    DrawRectangle(10, 50, static_cast<int>(barWidth), 20, GREEN);
}