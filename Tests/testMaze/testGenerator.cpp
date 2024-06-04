#include <gtest/gtest.h>
#include "raylib.h"
#include "../../levels/MazeLevel/mazeGenerator.h"

class MazeGeneratorTest : public ::testing::Test {
protected:
    const int mazeWidth = 10;
    const int mazeHeight = 10;
    const int numHotdogs = 5;
    std::vector<std::vector<Cell>> maze;
    std::vector<Rectangle> hotdogs;
    std::set<std::pair<int, int>> hotdogPositions;

    void SetUp() override {
        InitWindow(800, 600, "Test Window");
        maze.resize(mazeWidth, std::vector<Cell>(mazeHeight));
    }

    void TearDown() override {
        CloseWindow();
    }

    bool dfs(Cell& current, Cell& end, std::vector<std::vector<bool>>& visited) {
        if (&current == &end) return true;
        visited[current.x][current.y] = true;

        std::vector<Cell*> neighbors;

        if (!current.topWall && current.y > 0 && !visited[current.x][current.y - 1]) {
            neighbors.push_back(&maze[current.x][current.y - 1]);
        }
        if (!current.bottomWall && current.y < mazeHeight - 1 && !visited[current.x][current.y + 1]) {
            neighbors.push_back(&maze[current.x][current.y + 1]);
        }
        if (!current.leftWall && current.x > 0 && !visited[current.x - 1][current.y]) {
            neighbors.push_back(&maze[current.x - 1][current.y]);
        }
        if (!current.rightWall && current.x < mazeWidth - 1 && !visited[current.x + 1][current.y]) {
            neighbors.push_back(&maze[current.x + 1][current.y]);
        }

        for (Cell* neighbor : neighbors) {
            if (dfs(*neighbor, end, visited)) return true;
        }

        return false;
    }

    bool isPathBetweenCells(Cell& start, Cell& end) {
        std::vector<std::vector<bool>> visited(mazeWidth, std::vector<bool>(mazeHeight, false));
        return dfs(start, end, visited);
    }
};

TEST_F(MazeGeneratorTest, GenerateMaze) {
    MazeGenerator::Generate(maze, mazeWidth, mazeHeight);

    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            EXPECT_TRUE(maze[x][y].visited);
            bool hasAnyWallIntact = maze[x][y].topWall || maze[x][y].bottomWall || maze[x][y].leftWall || maze[x][y].rightWall;
            EXPECT_TRUE(hasAnyWallIntact);
        }
    }
}

TEST_F(MazeGeneratorTest, GenerateHotdogs) {
    MazeGenerator::GenerateHotdogs(hotdogs, maze, mazeWidth, mazeHeight, numHotdogs);

    EXPECT_EQ(hotdogs.size(), numHotdogs);

    for (const auto& hotdog : hotdogs) {
        int x = static_cast<int>(hotdog.x) / CELL_SIZE;
        int y = static_cast<int>(hotdog.y) / CELL_SIZE;

        EXPECT_TRUE(x >= 0 && x < mazeWidth);
        EXPECT_TRUE(y >= 0 && y < mazeHeight);

        EXPECT_TRUE(hotdogPositions.find({x, y}) == hotdogPositions.end());
        hotdogPositions.insert({x, y});
    }
}

TEST_F(MazeGeneratorTest, MazeConnectivity) {
    MazeGenerator::Generate(maze, mazeWidth, mazeHeight);

    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            for (int x2 = 0; x2 < mazeWidth; x2++) {
                for (int y2 = 0; y2 < mazeHeight; y2++) {
                    if (!(x == x2 && y == y2)) {
                        EXPECT_TRUE(isPathBetweenCells(maze[x][y], maze[x2][y2]));
                    }
                }
            }
        }
    }
}

TEST_F(MazeGeneratorTest, HotdogPositionValidity) {
    MazeGenerator::Generate(maze, mazeWidth, mazeHeight);
    MazeGenerator::GenerateHotdogs(hotdogs, maze, mazeWidth, mazeHeight, numHotdogs);

    for (const auto& hotdog : hotdogs) {
        int x = static_cast<int>(hotdog.x) / CELL_SIZE;
        int y = static_cast<int>(hotdog.y) / CELL_SIZE;

        EXPECT_TRUE(x >= 0 && x < mazeWidth);
        EXPECT_TRUE(y >= 0 && y < mazeHeight);


        EXPECT_TRUE(hotdogPositions.find({x, y}) == hotdogPositions.end());
        hotdogPositions.insert({x, y});
    }
}

TEST_F(MazeGeneratorTest, MazeDimensions) {
    ASSERT_EQ(maze.size(), mazeWidth);
    for (int x = 0; x < mazeWidth; x++) {
        ASSERT_EQ(maze[x].size(), mazeHeight);
    }
}

TEST_F(MazeGeneratorTest, HotdogCollisionWithWalls) {
    for (const auto& hotdog : hotdogs) {
        int hotdogX = static_cast<int>(hotdog.x) / CELL_SIZE;
        int hotdogY = static_cast<int>(hotdog.y) / CELL_SIZE;

        EXPECT_FALSE(maze[hotdogX][hotdogY].topWall);
        EXPECT_FALSE(maze[hotdogX][hotdogY].bottomWall);
        EXPECT_FALSE(maze[hotdogX][hotdogY].leftWall);
        EXPECT_FALSE(maze[hotdogX][hotdogY].rightWall);
    }
}

