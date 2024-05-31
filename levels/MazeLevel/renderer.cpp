#include "renderer.h"

void Renderer::DrawMazeWalls(const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, Texture2D& wallH, Texture2D& wallV) {
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            if (maze[x][y].topWall) {
                DrawTexture(wallH, x * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].bottomWall) {
                DrawTexture(wallH, x * CELL_SIZE, (y + 1) * CELL_SIZE, WHITE);
            }
            if (maze[x][y].leftWall) {
                DrawTexture(wallV, x * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].rightWall) {
                DrawTexture(wallV, (x + 1) * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
        }
    }
}

void Renderer::DrawHotdogsAndCollectedText(const std::vector<Rectangle>& hotdogs, int collectedHotdogs, Texture2D& hotdog) {
    for (const auto &hotdogRect: hotdogs) {
        if (hotdogRect.width > 0 && hotdogRect.height > 0) {
            DrawTexture(hotdog, hotdogRect.x, hotdogRect.y, WHITE);
        }
    }
    DrawText(TextFormat("Collected: %d/5", collectedHotdogs), 10, 10, 20, BLACK);
}