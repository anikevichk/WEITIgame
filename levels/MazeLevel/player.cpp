#include "player.h"

// Update player position and check collisions
void Player::UpdateAndCheckCollisions(Rectangle& player, const Vector2& direction, std::vector<std::vector<Cell>>& maze,
                                      int mazeWidth, int mazeHeight, std::vector<Rectangle>& hotdogs,
                                      int& collectedHotdogs, bool& gameWon, Rectangle& previousPosition, Sound& bonus) {
    // Calculate the new player position
    Rectangle newPlayerPos = {player.x + direction.x, player.y + direction.y, player.width, player.height};
    int x1 = static_cast<int>(newPlayerPos.x) / CELL_SIZE;
    int y1 = static_cast<int>(newPlayerPos.y) / CELL_SIZE;
    int x2 = static_cast<int>(newPlayerPos.x + newPlayerPos.width) / CELL_SIZE;
    int y2 = static_cast<int>(newPlayerPos.y + newPlayerPos.height) / CELL_SIZE;

    bool collision = false;
    // Check for collisions with maze walls
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

    // Move player if no collision, otherwise revert to previous position
    if (!collision) {
        player.x += direction.x;
        player.y += direction.y;
    } else {
        player = previousPosition;
    }

    // Check for collisions with hotdogs
    for (auto& hotdogRect : hotdogs) {
        if (CheckCollisionRecs(player, hotdogRect)) {
            // Play sound and remove hotdog
            PlaySound(bonus);
            hotdogRect = {-CELL_SIZE, -CELL_SIZE, 0, 0};
            collectedHotdogs++;
        }
    }

    // Check victory condition
    if (collectedHotdogs == 5 && player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
        gameWon = true;
    }
}

// Update player animation and draw
void Player::UpdateAndDrawAnimation(Rectangle& player, Rectangle currentFrames[], int& currentFrame,
                                    bool isKeyPressed, Texture2D& sprite, float scale) {
    static float frameTimer = 0.0f;
    const float frameRate = 0.1f;

    // Update animation frame
    frameTimer += GetFrameTime();
    if (frameTimer >= frameRate) {
        frameTimer = 0.0f;
        if (isKeyPressed) {
            currentFrame = (currentFrame + 1) % 3; // Loop through frames
        } else {
            currentFrame = 0; // Reset frame to idle
        }
    }

    // Draw player sprite
    Rectangle sourceRec = currentFrames[currentFrame];
    Rectangle destRec = {player.x, player.y, sourceRec.width * scale, sourceRec.height * scale};
    Vector2 origin = {sourceRec.width * scale / 600, sourceRec.height * scale / 24}; // Adjust origin for scaling
    DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);
}
