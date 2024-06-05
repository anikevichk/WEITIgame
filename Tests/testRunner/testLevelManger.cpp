#include <gtest/gtest.h>
#include "raylib.h"
#include "../../levels/RunnerLevel/levelManager.h"


class LevelManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<LevelManager> levelManager;
    void SetUp() override {
        InitWindow(100, 100, "test");
        levelManager = std::make_unique<LevelManager>();
        levelManager->InitLevel();
        levelManager->setLoss(false);
    }

    void TearDown() override {
        CloseWindow();
    }
};

TEST_F(LevelManagerTest, IsLossInitiallyFalse) {
    EXPECT_FALSE(levelManager->isLoss());
}

TEST_F(LevelManagerTest, SetLossTrue) {
    levelManager->setLoss(true);
    EXPECT_TRUE(levelManager->isLoss());
}

TEST_F(LevelManagerTest, RandomObstaclePosition) {
    levelManager->InitLevel();
    for (int i = 0; i < 6; ++i) {
        EXPECT_NE(0, levelManager->getObstacles(i).x);
    }
}

TEST_F(LevelManagerTest, CheckObstacleCollision) {
    levelManager->InitLevel();
    const auto obstacles = levelManager->getObstacles1();
    for (size_t i = 0; i < 6; ++i) {
        const Obstacle& obstacle = obstacles[i];
        levelManager->getPlayer().x = obstacle.x;
        levelManager->CheckObstacle();
        EXPECT_TRUE(levelManager->isLoss());
    }

}

TEST_F(LevelManagerTest, VictoryCondition) {
    levelManager->setCounter(50);
    EXPECT_TRUE(levelManager->isVictory());
}

TEST_F(LevelManagerTest, ObstacleResetPosition) {
    levelManager->InitLevel();

    auto& obstacle = levelManager->getObstacles(0);
    obstacle.x = -50;

    levelManager->CheckObstacle();

    EXPECT_GT(obstacle.x, levelManager->getScreenWidth());
}



TEST_F(LevelManagerTest, UpdateFrameIncreasesFrameCounter) {
    levelManager->InitLevel();
    auto& player = levelManager->getPlayer();
    levelManager->getPlayer().frameRate = 0;
    int initialFrame = player.currentFrame;

    levelManager->UpdateFrame();
    EXPECT_NE(initialFrame, player.currentFrame);
}

