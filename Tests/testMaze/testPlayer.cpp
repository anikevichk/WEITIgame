#include <gtest/gtest.h>
#include "../../levels/MazeLevel/player.h"

class PlayerTest : public ::testing::Test {
protected:
    Rectangle player;
    std::vector<std::vector<Cell>> maze;
    std::vector<Rectangle> hotdogs;
    int collectedHotdogs;
    bool gameWon;
    Rectangle previousPosition;
    Sound bonus;
    Rectangle currentFrames[3];
    int currentFrame;
    bool isKeyPressed;
    Texture2D sprite;

    void SetUp() override {
        player = {100, 100, 40, 40};
        maze.resize(10, std::vector<Cell>(10));
        hotdogs = {Rectangle{200, 200, 20, 20}};
        collectedHotdogs = 0;
        gameWon = false;
        previousPosition = player;
    }

    void TearDown() override {
        maze.clear();
        hotdogs.clear();
        collectedHotdogs = 0;
        gameWon = false;
        previousPosition = {0, 0, 0, 0};
    }

};

TEST_F(PlayerTest, UpdateAndCheckCollisions_NoCollision) {
    Vector2 direction = {10, 0};
    Player::UpdateAndCheckCollisions(player, direction, maze, 10, 10, hotdogs,
                                     collectedHotdogs, gameWon, previousPosition, bonus);
    EXPECT_EQ(player.x, 110);
    EXPECT_EQ(player.y, 100);
}

TEST_F(PlayerTest, UpdateAndCheckCollisions_Collision) {
    Vector2 direction = {0, -20};
    Player::UpdateAndCheckCollisions(player, direction, maze, 10, 10, hotdogs,
                                     collectedHotdogs, gameWon, previousPosition, bonus);
    EXPECT_EQ(player.x, 100);
    EXPECT_EQ(player.y, 80);
}

TEST_F(PlayerTest, UpdateAndCheckCollisions_CollectHotdog) {
    Rectangle hotdog = {player.x + 5, player.y + 5, 20, 20};
    hotdogs.push_back(hotdog);
    Vector2 direction = {0, 0};
    Player::UpdateAndCheckCollisions(player, direction, maze, 10, 10, hotdogs,
                                     collectedHotdogs, gameWon, previousPosition, bonus);
    EXPECT_EQ(collectedHotdogs, 1);

}
TEST_F(PlayerTest, UpdateAndCheckCollisions_GameWon) {
    collectedHotdogs = 5;
    player.x = 9 * CELL_SIZE + 5;
    player.y = CELL_SIZE - 5;
    Vector2 direction = {10, 0};
    Player::UpdateAndCheckCollisions(player, direction, maze, 10, 10, hotdogs,
                                     collectedHotdogs, gameWon, previousPosition, bonus);
    EXPECT_TRUE(gameWon);
}

