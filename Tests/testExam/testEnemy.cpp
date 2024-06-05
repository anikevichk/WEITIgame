#include <gtest/gtest.h>
#include "raylib.h"
#include "../../levels/ExamGameLevel/enemy.h"


class LevelManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<Enemy> levelManager;
    void SetUp() override {
        InitWindow(100, 100, "test");
        levelManager = std::make_unique<Enemy>(50,50,10,10,25,25);

    }

    void TearDown() override {
        CloseWindow();
    }
};



TEST_F(LevelManagerTest, EnemyReceivesDamage) {
    int initialHealth = levelManager->GetHealth();
    levelManager->ReceiveDamage(10);
    EXPECT_EQ(levelManager->GetHealth(), initialHealth - 10);
}

TEST_F(LevelManagerTest, EnemyMovesTowardsPlayer) {
    int initialX = levelManager->x;
    int initialY = levelManager->y;
    levelManager->moveToPlayer(100, 100);
    EXPECT_NE(levelManager->x, initialX);
    EXPECT_NE(levelManager->y, initialY);
}


TEST_F(LevelManagerTest, EnemyMovementIsConsistent) {
    int initialX = levelManager->x;
    int initialY = levelManager->y;
    levelManager->moveToPlayer(100, 100);
    int movedX = levelManager->x;
    int movedY = levelManager->y;
    EXPECT_TRUE((movedX == initialX + 1) || (movedX == initialX - 1) || (movedX == initialX));
    EXPECT_TRUE((movedY == initialY + 1) || (movedY == initialY - 1) || (movedY == initialY));
}











