#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "../Scenes/scenes.h"
#include "maze.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <ctime>


void Maze(Window &window) {
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 5.0f;
    SetTargetFPS(60);

    // Player animation variables
    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;

    // Arrays containing frames for player animation
    Rectangle runRightFrames[] = {
            {0,   0, 66, 95},
            {73,  0, 66, 95},
            {146, 0, 66, 95}
    };
    Rectangle runLeftFrames[] = {
            {0,   104, 66, 95},
            {73,  104, 66, 95},
            {146, 104, 66, 95}
    };
    Rectangle runBackFrames[] = {
            {0,   208, 73, 95},
            {75,  208, 73, 95},
            {158, 208, 73, 95}
    };
    Rectangle runForwardFrames[] = {
            {0,   312, 73, 95},
            {75,  312, 73, 95},
            {158, 312, 73, 95}
    };
    Rectangle *currentFrames = runRightFrames;

    // Number of horizontal and vertical cells
    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    // Player’s initial coordinates
    Rectangle player = {15, 807, 70.0f, 90.0f};

    // Create a two-dimensional vector to represent the maze
    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));
    // Generate the maze
    GenerateMaze(maze, mazeWidth, mazeHeight);

    // Load textures
    Texture2D hotdog, wallH, wallV, sprite, background;
    LoadTextures(hotdog, wallH, wallV, sprite, background);

    // Spawn 5 hotdogs in random positions
    std::vector<Rectangle> hotdogs;
    SpawnHotdogs(hotdogs, mazeWidth, mazeHeight);

    // Variables to track collected hotdogs and game state
    int collectedHotdogs = 0;
    bool gameWon = false;

    // Main game loop
    while (!WindowShouldClose()) {
        // Player movement direction vector
        Vector2 direction = {0, 0};

        // Update player position based on input
        UpdatePlayerPosition(player, direction, speed, isKeyPressed, currentFrames, runForwardFrames,
                             runBackFrames, runLeftFrames, runRightFrames, maze, mazeWidth, mazeHeight);

        // Check if player collected a hotdog
        CheckHotdogCollection(player, hotdogs, collectedHotdogs);

        // Check if player reached the top right corner (game goal)
        if (collectedHotdogs == 5 && player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
            gameWon = true;
        }

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Update frame timer and animate player
        AnimatePlayer(currentFrames, currentFrame, frameTimer, frameRate, isKeyPressed);

        DrawTexture(background, 0, 0, WHITE);

        // Draw player texture with offset
        DrawTextureRec(sprite, currentFrames[currentFrame],
                       (Vector2) {player.x + player.width / 2 - 66 / 2, player.y + player.height / 2 - 95 / 2},
                       WHITE);

        // Draw maze walls
        DrawMaze(maze, mazeWidth, mazeHeight, wallH, wallV);

        // Draw hotdogs
        for (const auto &hotdogRect: hotdogs) {
            if (hotdogRect.width > 0 && hotdogRect.height > 0) {
                DrawTexture(hotdog, hotdogRect.x, hotdogRect.y, WHITE);
            }
        }

        // Draw collected hotdogs counter
        DrawText(TextFormat("Collected: %d/5", collectedHotdogs), 10, 10, 20, BLACK);

        // Check if game is won
        if (gameWon) {
            window.setScreen(Window::VICTORY);
            break;
        }

        // End drawing
        EndDrawing();
    }

    // Unload textures
    UnloadTextures(hotdog, wallH, wallV, background);
}

// Function to load textures
void LoadTextures(Texture2D &hotdog, Texture2D &wallH, Texture2D &wallV, Texture2D &sprite, Texture2D &background) {
    hotdog = LoadTexture("../src/levelMaze/hotdog.png");
    wallH = LoadTexture("../src/levelMaze/wallH.png");
    wallV = LoadTexture("../src/levelMaze/wallV.png");
    sprite = LoadTexture("../src/levelMaze/sprite.png");
    background = LoadTexture("../src/levelMaze/background.png");
}

// Function to unload textures
void UnloadTextures(Texture2D hotdog, Texture2D wallH, Texture2D wallV, Texture2D background) {
    UnloadTexture(hotdog);
    UnloadTexture(wallH);
    UnloadTexture(wallV);
    UnloadTexture(background);
}

// Function to spawn hotdogs at random positions
void SpawnHotdogs(std::vector<Rectangle> &hotdogs, int mazeWidth, int mazeHeight) {
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        int hotdogX = rand() % mazeWidth;
        int hotdogY = rand() % mazeHeight;
        Rectangle hotdogRect = {static_cast<float>(hotdogX * CELL_SIZE + CELL_SIZE / 4),
                                static_cast<float>(hotdogY * CELL_SIZE + CELL_SIZE / 4), 75, 75};
        hotdogs.push_back(hotdogRect);
    }
}

// Function to update player's position based on input
void UpdatePlayerPosition(Rectangle &player, Vector2 &direction, float speed, bool &isKeyPressed,
                          Rectangle* &currentFrames, Rectangle runForwardFrames[], Rectangle runBackFrames[],
                          Rectangle runLeftFrames[], Rectangle runRightFrames[],
                          const std::vector<std::vector<Cell>> &maze, int mazeWidth, int mazeHeight) {
    Rectangle previousPosition = player;

    // Check player input for movement
    if (IsKeyDown(KEY_W)) {
        direction = {0, -speed};
        currentFrames = runForwardFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_S)) {
        direction = {0, speed};
        currentFrames = runBackFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_A)) {
        direction = {-speed, 0};
        currentFrames = runLeftFrames;
        isKeyPressed = true;
    } else if (IsKeyDown(KEY_D)) {
        direction = {speed, 0};
        currentFrames = runRightFrames;
        isKeyPressed = true;
    } else {
        isKeyPressed = false;
    }

    // Calculate new player position after movement
    Rectangle newPlayerPos = {player.x + direction.x, player.y + direction.y, player.width, player.height};

    // Check collision with maze walls
    if (!CheckCollisionWithWalls(newPlayerPos, maze, mazeWidth, mazeHeight)) {
        // No collision, move player
        player.x += direction.x;
        player.y += direction.y;
    } else {
        // Collision detected, restore previous position
        player = previousPosition;
    }
}

// Function to animate player based on frame timer
void AnimatePlayer(Rectangle* &currentFrames, int &currentFrame, float &frameTimer, float frameRate, bool isKeyPressed) {
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
}

// Function to check if player collected a hotdog
void CheckHotdogCollection(Rectangle &player, std::vector<Rectangle> &hotdogs, int &collectedHotdogs) {
    for (auto &hotdogRect: hotdogs) {
        if (CheckCollisionRecs(player, hotdogRect)) {
            // Remove collected hotdog from screen
            hotdogRect = {-CELL_SIZE, -CELL_SIZE, 0, 0};
            collectedHotdogs++;
        }
    }
}

// Function to generate the maze
void GenerateMaze(std::vector<std::vector<Cell>>& maze, int width, int height) {
    // Initialize maze cells
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            maze[x][y] = { x, y, false, true, true, true, true };
        }
    }

    // Use a stack to generate the maze
    std::stack<Cell*> stack;
    srand(time(0));
    int startX = rand() % width;
    int startY = rand() % height;
    maze[startX][startY].visited = true;
    stack.push(&maze[startX][startY]);

    while (!stack.empty()) {
        Cell* current = stack.top();
        std::vector<Cell*> neighbors;

        // Check unvisited neighbors
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
            // Randomly select a neighbor
            Cell* next = neighbors[rand() % neighbors.size()];

            // Remove wall between current and next cell
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

            // Mark next cell as visited and push it to the stack
            next->visited = true;
            stack.push(next);
        } else {
            // If no unvisited neighbors, pop current cell from stack
            stack.pop();
        }
    }
}

// Function to draw the maze
void DrawMaze(const std::vector<std::vector<Cell>>& maze, int width, int height, Texture2D wallH, Texture2D wallV) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Draw horizontal walls
            if (maze[x][y].topWall) {
                DrawTexture(wallH, x * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].bottomWall) {
                DrawTexture(wallH, x * CELL_SIZE, (y + 1) * CELL_SIZE , WHITE);
            }
            // Draw vertical walls
            if (maze[x][y].leftWall) {
                DrawTexture(wallV, x * CELL_SIZE , y * CELL_SIZE, WHITE);
            }
            if (maze[x][y].rightWall) {
                DrawTexture(wallV, (x + 1) * CELL_SIZE, y * CELL_SIZE, WHITE);
            }
        }
    }
}

// Function to check collision with maze walls
bool CheckCollisionWithWalls(Rectangle player, const std::vector<std::vector<Cell>>& maze, int width, int height) {
    // Calculate player coordinates in maze cells
    int x1 = static_cast<int>(player.x) / CELL_SIZE;
    int y1 = static_cast<int>(player.y) / CELL_SIZE;
    int x2 = static_cast<int>(player.x + player.width) / CELL_SIZE;
    int y2 = static_cast<int>(player.y + player.height) / CELL_SIZE;

    // Check all cells occupied by the player
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                Cell cell = maze[x][y];

                // Check cell walls
                if (cell.topWall && player.y <= y * CELL_SIZE) return true;
                if (cell.bottomWall && player.y + player.height >= (y + 1) * CELL_SIZE) return true;
                if (cell.leftWall && player.x <= x * CELL_SIZE) return true;
                if (cell.rightWall && player.x + player.width >= (x + 1) * CELL_SIZE) return true;
            }
        }
    }

    return false;
}
