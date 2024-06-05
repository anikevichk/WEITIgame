#include <gtest/gtest.h>
#include "raylib.h"
#include "../../levels/ExamGameLevel/Player.h"


class LevelManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<Player> levelManager;
    void SetUp() override {
        InitWindow(100, 100, "test");
        levelManager = std::make_unique<Player>(50,50,10,10,100);

    }

    void TearDown() override {
        CloseWindow();
    }
};

TEST_F(LevelManagerTest, HealthDecreasesWhenDamaged) {
    int initialHealth = levelManager->GetHealth();
    levelManager->ReceiveDamage(10);
    EXPECT_EQ(levelManager->GetHealth(), initialHealth - 10);
}


TEST_F(LevelManagerTest, DamageTimerResetsAfterDamage) {
    levelManager->ReceiveDamage(10);
    EXPECT_EQ(levelManager->getDamageTimer(), levelManager->getDamageRate());
}


TEST_F(LevelManagerTest, PlayerHealthRestoresAfterEating) {
    levelManager->ReceiveDamage(50);
    int damagedHealth = levelManager->GetHealth();
    levelManager->ReceiveDamage(-30);
    EXPECT_GT(levelManager->GetHealth(), damagedHealth);
}

TEST_F(LevelManagerTest, PlayerFrameSizeInitialization) {
    EXPECT_EQ(levelManager->getFrameSize(), 25);
}


TEST_F(LevelManagerTest, PlayerHealthIsNotOverMaxAfterHealing) {
    levelManager->ReceiveDamage(-50);
    EXPECT_LE(levelManager->GetHealth(), 100);
}



TEST_F(LevelManagerTest, PlayerSpeedDoesNotChangeAfterDamage) {
    float speedBefore = levelManager->getSpeed();
    levelManager->ReceiveDamage(10);
    float speedAfter = levelManager->getSpeed();
    EXPECT_EQ(speedBefore, speedAfter);
}



