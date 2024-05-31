#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
#include "raylib.h"
#include "cell.h"

class MazeGenerator {
public:
    static void Generate(std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight);
    static void GenerateHotdogs(std::vector<Rectangle>& hotdogs, std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, int numHotdogs);
};

#endif // MAZEGENERATOR_H