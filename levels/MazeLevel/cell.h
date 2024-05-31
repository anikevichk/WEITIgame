#ifndef CELL_H
#define CELL_H
const int CELL_SIZE = 100;

class Cell {
public:
    int x, y;
    bool visited;
    bool topWall, bottomWall, leftWall, rightWall;
};

#endif // CELL_H