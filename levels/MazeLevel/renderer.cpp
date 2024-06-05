#include "renderer.h"

// Function to draw maze walls based on the maze structure
void Renderer::DrawMazeWalls(const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, Texture2D& wallH, Texture2D& wallV) {
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            // Draw horizontal walls
            if (maze[x][y].topWall) {
                DrawTexture(wallH, x * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].bottomWall) {
                DrawTexture(wallH, x * CELL_SIZE, (y + 1) * CELL_SIZE, WHITE);
            }
            // Draw vertical walls
            if (maze[x][y].leftWall) {
                DrawTexture(wallV, x * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].rightWall) {
                DrawTexture(wallV, (x + 1) * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
        }
    }
}

// Function to draw hotdogs and display the number of collected hotdogs
void Renderer::DrawHotdogsAndCollectedText(const std::vector<Rectangle>& hotdogs, int collectedHotdogs, Texture2D& hotdog) {
    // Draw each hotdog
    for (const auto &hotdogRect : hotdogs) {
        if (hotdogRect.width > 0 && hotdogRect.height > 0) {
            DrawTexture(hotdog, hotdogRect.x, hotdogRect.y, WHITE);
        }
    }
    // Display number of collected hotdogs
    DrawText(TextFormat("Collected: %d/5", collectedHotdogs), 10, 10, 20, BLACK);
}
