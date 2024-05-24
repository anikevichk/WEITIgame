#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "../Scenes/scenes.h"
#include "maze.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <ctime>

// Main function for display of maze and player control
void Maze(Window &window) {
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 5.0f;
    SetTargetFPS(60);

    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;

    Rectangle runRightFrames[] = {                              //frames for player animation
            {0,  0, 66, 95},
            {73, 0, 66, 95},
            {146, 0, 66, 95}
    };

    Rectangle runLeftFrames[] = {                              //frames for player animation
            {0,  104, 66, 95},
            {73, 104, 66, 95},
            {146, 104, 66, 95}
    };

    Rectangle runBackFrames[] = {                              //frames for player animation
            {0,  208, 73, 95},
            {75,  208, 73, 95},
            {158,  208, 73, 95}
    };

    Rectangle runForwardFrames[] = {                              //frames for player animation
            {0,  312, 73, 95},
            {75,  312, 73, 95},
            {158,  312, 73, 95}
    };

    Rectangle* currentFrames = runRightFrames;

    // Number of horizontal and vertical cells
    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    // Player’s initial coordinates (centre of left lower cell)
    Rectangle player = { static_cast<float>(CELL_SIZE / 2), static_cast<float>((mazeHeight - 1) * CELL_SIZE + CELL_SIZE / 2), 25.0f, 25.0f };

    // Create a two-dimensional vector to represent the maze
    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));

    GenerateMaze(maze, mazeWidth, mazeHeight);

    // Load textures
    Texture2D hotdog = LoadTexture("../src/levelMaze/hotdog.png");
    Texture2D wallH = LoadTexture("../src/levelMaze/wallH.png");
    Texture2D wallV = LoadTexture("../src/levelMaze/wallV.png");
    Texture2D sprite = LoadTexture("../src/levelMaze/sprite.png");

    // Spawn 5 hotdogs in random positions
    srand(time(0));
    std::vector<Rectangle> hotdogs;
    for (int i = 0; i < 5; i++) {
        int hotdogX = rand() % mazeWidth;
        int hotdogY = rand() % mazeHeight;
        Rectangle hotdogRect = { static_cast<float>(hotdogX * CELL_SIZE + CELL_SIZE / 4), static_cast<float>(hotdogY * CELL_SIZE + CELL_SIZE / 4), 75, 75};
        hotdogs.push_back(hotdogRect);
    }

    int collectedHotdogs = 0;
    bool gameWon = false;

    while (!WindowShouldClose()) {
        Vector2 direction = { 0, 0 }; // Vector of the player’s direction
        Rectangle previousPosition = player; // Store previous position

        if (IsKeyDown(KEY_W)) {
            direction = { 0, -speed };
            currentFrames = runForwardFrames;
            isKeyPressed = true;
        }
        else if (IsKeyDown(KEY_S)) {
            direction = { 0, speed };
            currentFrames = runBackFrames;
            isKeyPressed = true;
        }
        else if (IsKeyDown(KEY_A)) {
            direction = { -speed, 0 };
            currentFrames = runLeftFrames;
            isKeyPressed = true;
        }
        else if (IsKeyDown(KEY_D)) {
            direction = { speed, 0 };
            currentFrames = runRightFrames;
            isKeyPressed = true;
        } else {
            isKeyPressed = false;
        }

        // New position after movement


        Rectangle newPlayerPos = { player.x + direction.x, player.y + direction.y, player.width, player.height };

        // Check for collision of player with maze walls
        if (!CheckCollisionWithWalls(newPlayerPos, maze, mazeWidth, mazeHeight)) {
            // No collision, move the player
            player.x += direction.x;
            player.y += direction.y;
        } else {
            // Collision detected, restore previous position
            player = previousPosition;
        }

        // Check if the player has collected a hotdog
        for (auto& hotdogRect : hotdogs) {
            if (CheckCollisionRecs(player, hotdogRect)) {
                hotdogRect = { -CELL_SIZE, -CELL_SIZE, 0, 0 }; // Remove the collected hotdog behind the screen
                collectedHotdogs++;
            }
        }

        // Check upper right corner (game goal)
        if (collectedHotdogs == 5 && player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
            gameWon = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        frameTimer += GetFrameTime();   //frame changer
        if (frameTimer >= frameRate) {
            frameTimer = 0.0f;
            if(isKeyPressed) {
                currentFrame++;
                if (currentFrame >= 3) {
                    currentFrame = 0;
                }
            } else currentFrame = 0;
        }

        DrawTextureRec(sprite, currentFrames[currentFrame], (Vector2) {player.x - 45, player.y - 50}, WHITE);
        DrawMaze(maze, mazeWidth, mazeHeight, wallH, wallV);

        // Drawing of hotdogs
        for (const auto& hotdogRect : hotdogs) {
            if (hotdogRect.width > 0 && hotdogRect.height > 0) { // Draw only hotdogs that have not been collected
                DrawTexture(hotdog, hotdogRect.x, hotdogRect.y, WHITE);
            }
        }

        DrawText(TextFormat("Collected: %d/5", collectedHotdogs), 10, 10, 20, BLACK);

        if (gameWon) {
            window.setScreen(Window::VICTORY);
            break;
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(hotdog);
    UnloadTexture(wallH);
    UnloadTexture(wallV);
}

void GenerateMaze(std::vector<std::vector<Cell>>& maze, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            maze[x][y] = { x, y, false, true, true, true, true };
        }
    }

    std::stack<Cell*> stack;
    srand(time(0));
    int startX = rand() % width;
    int startY = rand() % height;
    maze[startX][startY].visited = true;
    stack.push(&maze[startX][startY]);

    while (!stack.empty()) {
        Cell* current = stack.top();
        std::vector<Cell*> neighbors;

        if (current->x > 0 && !maze[current->x - 1][current->y].visited) {
            neighbors.push_back(&maze[current->x - 1][current->y]);
        }
        if (current->x < width - 1 && !maze[current->x + 1][current->y].visited) {
            neighbors.push_back(&maze[current->x + 1][current->y]);
        }
        if (current->y > 0 && !maze[current->x][current->y - 1].visited) {
            neighbors.push_back(&maze[current->x][current->y - 1]);
        }
        if (current->y < height - 1 && !maze[current->x][current->y + 1].visited) {
            neighbors.push_back(&maze[current->x][current->y + 1]);
        }

        if (!neighbors.empty()) {
            Cell* next = neighbors[rand() % neighbors.size()];

            if (next->x == current->x - 1) {
                current->leftWall = false;
                next->rightWall = false;
            } else if (next->x == current->x + 1) {
                current->rightWall = false;
                next->leftWall = false;
            } else if (next->y == current->y - 1) {
                current->topWall = false;
                next->bottomWall = false;
            } else if (next->y == current->y + 1) {
                current->bottomWall = false;
                next->topWall = false;
            }

            next->visited = true;
            stack.push(next);
        } else {
            stack.pop();
        }
    }
}

void DrawMaze(const std::vector<std::vector<Cell>>& maze, int width, int height, Texture2D wallH, Texture2D wallV) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (maze[x][y].topWall) {
                DrawTexture(wallH, x * CELL_SIZE, y * CELL_SIZE - 2, WHITE);
            }
            if (maze[x][y].bottomWall) {
                DrawTexture(wallH, x * CELL_SIZE, (y + 1) * CELL_SIZE - 2, WHITE);
            }
            if (maze[x][y].leftWall) {
                DrawTexture(wallV, x * CELL_SIZE - 2, y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].rightWall) {
                DrawTexture(wallV, (x + 1) * CELL_SIZE - 2, y * CELL_SIZE, WHITE);
            }
        }
    }
}

bool CheckCollisionWithWalls(Rectangle player, const std::vector<std::vector<Cell>>& maze, int width, int height) {
    int x = player.x / CELL_SIZE;
    int y = player.y / CELL_SIZE;

    if (x >= 0 && x < width && y >= 0 && y < height) {
        Cell cell = maze[x][y];

        if (cell.topWall && player.y - player.height - 20<= y * CELL_SIZE) return true;
        if (cell.bottomWall && player.y + player.height + 20>= (y +1) * CELL_SIZE) return true;
        if (cell.leftWall && player.x - player.width - 20 <= x * CELL_SIZE + 5) return true;
        if (cell.rightWall && player.x + player.width - 5>= (x + 1) * CELL_SIZE + 5) return true;
    }

    return false;
}
