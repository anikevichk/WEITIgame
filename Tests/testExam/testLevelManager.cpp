#include <gtest/gtest.h>
#include "raylib.h"
#include "../../levels/ExamGameLevel/levelManager.h"


class LevelManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<levelManager> Manager;
    void SetUp() override {
        InitWindow(100, 100, "test");
        Window currentWindow;
        currentWindow.setScreen(Window::EXAM);
        Manager = std::make_unique<levelManager>(currentWindow);
        Manager->Update();
    }

    void TearDown() override {
        CloseWindow();
    }
};


TEST_F(LevelManagerTest, HotdogSpawning) {
    Manager->UpdateHotdog();
    Hotdog hotdog = Manager->getHotdog();
    EXPECT_NE(hotdog.x, -30);
    EXPECT_NE(hotdog.y, -30);
}

TEST_F(LevelManagerTest, EnemySpawning) {
    Manager->UpdateEnemy();
    auto enemies = Manager->enemies;
    EXPECT_GT(enemies.size(), 0);
}

TEST_F(LevelManagerTest, PlayerHealthAfterDamage) {
    Player player = Manager->getPlayer();
    int initialHealth = player.GetHealth();
    player.ReceiveDamage(10);
    EXPECT_EQ(player.GetHealth(), initialHealth - 10);
}

TEST_F(LevelManagerTest, BulletTextureAssignment) {
    auto bullets = Manager->bullets;
    Manager->UpdateBullets();
    for (const auto& bullet : bullets) {
        EXPECT_GE(bullet.texture, 0);
        EXPECT_LT(bullet.texture, 10);
    }
}

TEST_F(LevelManagerTest, HotdogTimerResetAfterSpawn) {
    Manager->UpdateHotdog();
    Hotdog hotdog = Manager->getHotdog();
    EXPECT_EQ(hotdog.hotDogTimer, 0.0f);
}

TEST_F(LevelManagerTest, EnemyHealthAfterDamage) {
    Manager->UpdateEnemy();
    auto enemies = Manager->enemies;
    for (auto& enemy : enemies) {
        int initialHealth = enemy.GetHealth();
        enemy.ReceiveDamage(10);
        EXPECT_EQ(enemy.GetHealth(), initialHealth - 10);
    }
}

TEST_F(LevelManagerTest, PlayerMovementBoundaries) {
    Player player = Manager->getPlayer();
    Manager->CheckButtons();
    EXPECT_GE(player.x, 0);
    EXPECT_LE(player.x, Manager->getScreenWidth());
    EXPECT_GE(player.y, 0);
    EXPECT_LE(player.y, Manager->getScreenHeight());
}

TEST_F(LevelManagerTest, BulletRemovalAfterHit) {
    Manager->UpdateBullets();
    auto bullets = Manager->bullets;
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) {
            return b.hit;
    }), bullets.end());
    for (const auto& bullet : bullets) {
        EXPECT_FALSE(bullet.hit);
    }
}

TEST_F(LevelManagerTest, EnemyRemovalAfterDeath) {
    Manager->UpdateEnemy();
    auto enemies = Manager->enemies;
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& enemy) {
            return enemy.GetHealth() <= 0;
    }), enemies.end());
    for (Enemy enemy : enemies) {
        EXPECT_GT(enemy.GetHealth(), 0);
    }
}



TEST_F(LevelManagerTest, BulletRotationMatchesDirection) {

    Manager->CheckButtons();
    auto bullets = Manager->bullets;
    for (const auto& bullet : bullets) {
        if (bullet.speed.x > 0) {
            EXPECT_EQ(bullet.rotate, 180.0f);
        } else if (bullet.speed.y > 0) {
            EXPECT_EQ(bullet.rotate, 270.0f);
        }
    }
}
