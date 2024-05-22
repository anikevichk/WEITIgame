#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "../Scenes/scenes.h"
#include "maze.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <ctime>


// Function to draw the maze and player
void DrawGame(const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, const Rectangle& player, bool gameWon) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawMaze(maze, mazeWidth, mazeHeight);
    DrawRectangleRec(player, BLUE);

    if (gameWon) {
        DrawText("You Win!", GetScreenWidth() / 2 - MeasureText("You Win!", 40) / 2, GetScreenHeight() / 2 - 20, 40, GREEN);
    }

    EndDrawing();
}


void UpdatePlayer(Rectangle& player, float speed, const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, bool& gameWon) {
    Vector2 direction = { 0, 0 }; // Player movement direction vector

    // Handle key inputs for player movement
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

    // Check for player collision with maze walls
    if (!CheckCollisionWithWalls(newPlayerPos, maze, mazeWidth, mazeHeight)) {
        player.x += direction.x;
        player.y += direction.y;
    }

    // Check top right corner (game objective)
    if (player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
        gameWon = true;
    }
}

// Main function for displaying the maze and controlling the player
void Maze(Window &window) {
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 5.0f;
    SetTargetFPS(60);

    // Number of cells horizontally and vertically
    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    // Player's initial coordinates (center left lower cell)
    Rectangle player = { static_cast<float>(CELL_SIZE / 2), static_cast<float>((mazeHeight - 1) * CELL_SIZE + CELL_SIZE / 2), 25.0f, 25.0f };

    // Create a 2D vector to represent the maze
    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));

    // Generate the maze
    GenerateMaze(maze, mazeWidth, mazeHeight);

    bool gameWon = false;

    while (!WindowShouldClose()) {
        UpdatePlayer(player, speed, maze, mazeWidth, mazeHeight, gameWon); // Update player state
        DrawGame(maze, mazeWidth, mazeHeight, player, gameWon); // Draw maze and player
    }

    CloseWindow();
}


void GenerateMaze(std::vector<std::vector<Cell>>& maze, int width, int height) {
    /*
    For each maze cell at [x][y] the initial values are set:
    x and y are cell coordinates,
    false - a flag indicating that the cell has not yet been visited (for the maze generation algorithm),
    true - flags indicating the presence of walls at the cell. In this case, all walls are set in the state of "true".
    */
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            maze[x][y] = { x, y, false, true, true, true, true };
        }
    }

    std::stack<Cell*> stack;                // Stack to execute the algorithm Recursive Backtracking (DFS)

    srand(time(0));              // Initialization of the random number generator
    // Random starting position Y and X
    int startX = rand() % width;
    int startY = rand() % height;

    maze[startX][startY].visited = true;    // Initial cell marked as visited
    stack.push(&maze[startX][startY]);   // Adding the starting cell to the stack


    while (!stack.empty()) {
        Cell* current = stack.top();
        std::vector<Cell*> neighbors;

        // Checking the possibility of moving to the left
        if (current->x > 0 && !maze[current->x - 1][current->y].visited) {
            neighbors.push_back(&maze[current->x - 1][current->y]);
        }
        // Checking the possibility of moving to the right
        if (current->x < width - 1 && !maze[current->x + 1][current->y].visited) {
            neighbors.push_back(&maze[current->x + 1][current->y]);
        }
        // Checking the possibility of moving upwards
        if (current->y > 0 && !maze[current->x][current->y - 1].visited) {
            neighbors.push_back(&maze[current->x][current->y - 1]);
        }
        // Checking the possibility of moving downwards
        if (current->y < height - 1 && !maze[current->x][current->y + 1].visited) {
            neighbors.push_back(&maze[current->x][current->y + 1]);
        }

        // Choosing a random neighbor to continue the journey
        if (!neighbors.empty()) {
            Cell* next = neighbors[rand() % neighbors.size()];

            // Remove wall between current cell and selected neighbor
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
            stack.pop(); // Remove the current cell from the stack if no neighbors are available
        }
    }
}

void DrawMaze(const std::vector<std::vector<Cell>>& maze, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Draw cell walls if they exist
            if (maze[x][y].topWall) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, 2, BLACK);
            }
            if (maze[x][y].bottomWall) {
                DrawRectangle(x * CELL_SIZE, (y + 1) * CELL_SIZE - 2, CELL_SIZE, 2, BLACK);
            }
            if (maze[x][y].leftWall) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, 2, CELL_SIZE, BLACK);
            }
            if (maze[x][y].rightWall) {
                DrawRectangle((x + 1) * CELL_SIZE - 2, y * CELL_SIZE, 2, CELL_SIZE, BLACK);
            }
        }
    }
}

// Функция для проверки столкновений игрока с стенами лабиринта
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
