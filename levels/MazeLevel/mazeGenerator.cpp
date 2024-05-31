#include "mazeGenerator.h"
#include <stack>
#include <ctime>
#include <set>
#include <algorithm>

void MazeGenerator::Generate(std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight) {
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            maze[x][y] = {x, y, false, true, true, true, true};
        }
    }

    std::stack<Cell*> stack;
    srand(time(0));
    int startX = rand() % mazeWidth;
    int startY = rand() % mazeHeight;
    maze[startX][startY].visited = true;
    stack.push(&maze[startX][startY]);

    while (!stack.empty()) {
        Cell* current = stack.top();
        std::vector<Cell*> neighbors;

        if (current->x > 0 && !maze[current->x - 1][current->y].visited) {
            neighbors.push_back(&maze[current->x - 1][current->y]);
        }
        if (current->x < mazeWidth - 1 && !maze[current->x + 1][current->y].visited) {
            neighbors.push_back(&maze[current->x + 1][current->y]);
        }
        if (current->y > 0 && !maze[current->x][current->y - 1].visited) {
            neighbors.push_back(&maze[current->x][current->y - 1]);
        }
        if (current->y < mazeHeight - 1 && !maze[current->x][current->y + 1].visited) {
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

void MazeGenerator::GenerateHotdogs(std::vector<Rectangle>& hotdogs, std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight, int numHotdogs) {
    hotdogs.clear(); // Clear current hotdog positions
    std::set<std::pair<int, int>> occupiedCells; // Track occupied cells
    srand(time(0)); // Initialize random number generator

    // Generate positions for each hotdog
    while (hotdogs.size() < numHotdogs) {
        int hotdogX = rand() % mazeWidth;
        int hotdogY = rand() % mazeHeight;

        // Check if this cell is already occupied
        if (occupiedCells.find({hotdogX, hotdogY}) == occupiedCells.end()) {
            // Create a rectangle for the hotdog and add it to the vector
            Rectangle hotdogRect = {static_cast<float>(hotdogX * CELL_SIZE + CELL_SIZE / 4),
                                    static_cast<float>(hotdogY * CELL_SIZE + CELL_SIZE / 4), 75, 75};
            hotdogs.push_back(hotdogRect);

            // Add position to occupied cells
            occupiedCells.insert({hotdogX, hotdogY});
        }
    }
}