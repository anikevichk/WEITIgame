#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "raylib.h"
#include "../../Tools/Window.h"

// Size of the maze cell
#define CELL_SIZE 100

// Structure representing the maze cell
struct Cell {
    int x, y;
    bool visited;
    bool topWall, bottomWall, leftWall, rightWall;
};

void Maze(Window &window);
void GenerateMaze(std::vector<std::vector<Cell>>& maze, int width, int height);
void DrawMaze(const std::vector<std::vector<Cell>>& maze, int width, int height, Texture2D wallH, Texture2D wallV);
bool CheckCollisionWithWalls(Rectangle player, const std::vector<std::vector<Cell>>& maze, int width, int height);
void LoadTextures(Texture2D &hotdog, Texture2D &wallH, Texture2D &wallV, Texture2D &sprite, Texture2D &background);
void UnloadTextures(Texture2D hotdog, Texture2D wallH, Texture2D wallV, Texture2D background);
void InitializePlayer(Rectangle &player);
void SpawnHotdogs(std::vector<Rectangle> &hotdogs, int mazeWidth, int mazeHeight);
void UpdatePlayerPosition(Rectangle &player, Vector2 &direction, float speed, bool &isKeyPressed, Rectangle* &currentFrames, Rectangle runForwardFrames[], Rectangle runBackFrames[], Rectangle runLeftFrames[], Rectangle runRightFrames[], const std::vector<std::vector<Cell>> &maze, int mazeWidth, int mazeHeight);
void AnimatePlayer(Rectangle* &currentFrames, int &currentFrame, float &frameTimer, float frameRate, bool isKeyPressed);
void CheckHotdogCollection(Rectangle &player, std::vector<Rectangle> &hotdogs, int &collectedHotdogs);

#endif // MAZE_H
