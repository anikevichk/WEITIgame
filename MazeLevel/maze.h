#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"

// Size of the maze cell
#define CELL_SIZE 200

// Structure representing the maze cell
struct Cell {
    int x, y;
    bool visited;
    bool topWall, bottomWall, leftWall, rightWall;
};

void DrawGame(const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, const Rectangle& player, bool gameWon);
void UpdatePlayer(Rectangle& player, float speed, const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, bool& gameWon);
void Maze(Window &window);
void GenerateMaze(std::vector<std::vector<Cell>>& maze, int width, int height);
void DrawMaze(const std::vector<std::vector<Cell>>& maze, int width, int height);
bool CheckCollisionWithWalls(Rectangle player, const std::vector<std::vector<Cell>>& maze, int width, int height);

#endif // MAZE_H
