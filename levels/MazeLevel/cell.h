#ifndef CELL_H
#define CELL_H

// Constant representing the size of each cell
const int CELL_SIZE = 100;

// Class representing a single cell in a grid-based environment
class Cell {
public:
    int x, y;               // Coordinates of the cell
    bool visited;           // Flag indicating whether the cell has been visited
    bool topWall, bottomWall, leftWall, rightWall;   // Flags representing presence of walls
};

#endif // CELL_H
