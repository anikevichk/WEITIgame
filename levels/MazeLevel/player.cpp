#include "player.h"
void Player::UpdateAndCheckCollisions(Rectangle& player, const Vector2& direction, std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, std::vector<Rectangle>& hotdogs, int& collectedHotdogs, bool& gameWon, Rectangle& previousPosition, Sound& bonus) {
    Rectangle newPlayerPos = {player.x + direction.x, player.y + direction.y, player.width, player.height};
    int x1 = static_cast<int>(newPlayerPos.x) / CELL_SIZE;
    int y1 = static_cast<int>(newPlayerPos.y) / CELL_SIZE;
    int x2 = static_cast<int>(newPlayerPos.x + newPlayerPos.width) / CELL_SIZE;
    int y2 = static_cast<int>(newPlayerPos.y + newPlayerPos.height) / CELL_SIZE;

    bool collision = false;
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            if (x >= 0 && x < mazeWidth && y >= 0 && y < mazeHeight) {
                Cell cell = maze[x][y];
                if (cell.topWall && newPlayerPos.y <= y * CELL_SIZE) collision = true;
                if (cell.bottomWall && newPlayerPos.y + newPlayerPos.height >= (y + 1) * CELL_SIZE) collision = true;
                if (cell.leftWall && newPlayerPos.x <= x * CELL_SIZE) collision = true;
                if (cell.rightWall && newPlayerPos.x + newPlayerPos.width >= (x + 1) * CELL_SIZE) collision = true;
            }
        }
    }

    if (!collision) {
        player.x += direction.x;
        player.y += direction.y;
    } else {
        // Return player to previous position on collision
        player = previousPosition;
    }

    for (auto &hotdogRect: hotdogs) {
        if (CheckCollisionRecs(player, hotdogRect)) {
            // Play sound and remove hotdog
            PlaySound(bonus);
            hotdogRect = {-CELL_SIZE, -CELL_SIZE, 0, 0};
            collectedHotdogs++;
        }
    }

    // Check if victory condition is met
    if (collectedHotdogs == 5 && player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
        gameWon = true;
    }
}
void Player::UpdateAndDrawAnimation(Rectangle& player, Rectangle currentFrames[], int& currentFrame, bool isKeyPressed, Texture2D& sprite, float scale) {
    static float frameTimer = 0.0f;
    const float frameRate = 0.1f;

    frameTimer += GetFrameTime();
    if (frameTimer >= frameRate) {
        frameTimer = 0.0f;
        if (isKeyPressed) {
            currentFrame++;
            if (currentFrame >= 3) {
                currentFrame = 0;
            }
        } else {
            currentFrame = 0;
        }
    }

    Rectangle sourceRec = currentFrames[currentFrame];
    Rectangle destRec = {player.x, player.y, sourceRec.width * scale, sourceRec.height * scale};
    Vector2 origin = {sourceRec.width * scale / 600, sourceRec.height * scale / 24};
    DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
}