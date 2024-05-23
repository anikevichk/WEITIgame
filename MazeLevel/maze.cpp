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

    // Number of horizontal and vertical cells
    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    // Player’s initial coordinates (centre of left lower cell)
    Rectangle player = { static_cast<float>(CELL_SIZE / 2), static_cast<float>((mazeHeight - 1) * CELL_SIZE + CELL_SIZE / 2), 25.0f, 25.0f };

    // Create a two-dimensional vector to represent the maze
    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));

    GenerateMaze(maze, mazeWidth, mazeHeight);

    // Spawn 5 red squares in random positions
    srand(time(0));
    std::vector<Rectangle> redSquares;
    for (int i = 0; i < 5; i++) {
        int redSquareX = rand() % mazeWidth;
        int redSquareY = rand() % mazeHeight;
        Rectangle redSquare = { static_cast<float>(redSquareX * CELL_SIZE + CELL_SIZE / 4), static_cast<float>(redSquareY * CELL_SIZE + CELL_SIZE / 4), 25, 25};
        redSquares.push_back(redSquare);
    }

    int collectedSquares = 0;
    bool gameWon = false;

    while (!WindowShouldClose()) {
        Vector2 direction = { 0, 0 }; // Vector of the player’s direction

        // Keystroke handling for player control
        if (IsKeyDown(KEY_W)) {
            direction.y = -speed;
        }
        if (IsKeyDown(KEY_S)) {
            direction.y = speed;
        }
        if (IsKeyDown(KEY_A)) {
            direction.x = -speed;
        }
        if (IsKeyDown(KEY_D)) {
            direction.x = speed;
        }

        Rectangle newPlayerPos = { player.x + direction.x, player.y + direction.y, player.width, player.height };

        // Check for collision of player with maze walls
        if (!CheckCollisionWithWalls(newPlayerPos, maze, mazeWidth, mazeHeight)) {
            player.x += direction.x;
            player.y += direction.y;
        }

        // Check if the player has collected a red square
        for (auto& redSquare : redSquares) {
            if (CheckCollisionRecs(player, redSquare)) {
                redSquare = { -CELL_SIZE, -CELL_SIZE, 0, 0 }; // Remove the assembled square behind the screen
                collectedSquares++;
            }
        }

        // Check upper right corner (game goal)
        if (collectedSquares == 5 && player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
            gameWon = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawMaze(maze, mazeWidth, mazeHeight);

        // Drawing of red squares
        for (const auto& redSquare : redSquares) {
            if (redSquare.width > 0 && redSquare.height > 0) { // Draw only squares that have not been collected
                DrawRectangleRec(redSquare, RED);
            }
        }

        DrawRectangleRec(player, BLUE);
        DrawText(TextFormat("Collected: %d/5", collectedSquares), 10, 10, 20, BLACK);

        if (gameWon) {
            window.setScreen(Window::VICTORY);
            break;
        }

        EndDrawing();
    }
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

void DrawMaze(const std::vector<std::vector<Cell>>& maze, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (maze[x][y].topWall) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, 5, BLACK);
            }
            if (maze[x][y].bottomWall) {
                DrawRectangle(x * CELL_SIZE, (y + 1) * CELL_SIZE - 2, CELL_SIZE, 5, BLACK);
            }
            if (maze[x][y].leftWall) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, 5, CELL_SIZE, BLACK);
            }
            if (maze[x][y].rightWall) {
                DrawRectangle((x + 1) * CELL_SIZE - 2, y * CELL_SIZE, 5, CELL_SIZE, BLACK);
            }
        }
    }
}

bool CheckCollisionWithWalls(Rectangle player, const std::vector<std::vector<Cell>>& maze, int width, int height) {
    int x = player.x / CELL_SIZE;
    int y = player.y / CELL_SIZE;

    if (x >= 0 && x < width && y >= 0 && y < height) {
        Cell cell = maze[x][y];

        if (cell.topWall && player.y <= y * CELL_SIZE) return true;
        if (cell.bottomWall && player.y + player.height >= (y + 1) * CELL_SIZE) return true;
        if (cell.leftWall && player.x <= x * CELL_SIZE) return true;
        if (cell.rightWall && player.x + player.width >= (x + 1) * CELL_SIZE) return true;
    }

    return false;
}
