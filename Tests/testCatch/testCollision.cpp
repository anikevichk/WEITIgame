#include "gtest/gtest.h"
#include "../../levels/CatchLevel/collision.h"


TEST(CollisionTest, MoveSpecialFruitsTest) {
    Rectangle veryGoodFruit {0, 0, 10, 10};
    Rectangle veryBadFruit {0, 0, 10, 10};

    collision::MoveSpecialFruits(veryGoodFruit, veryBadFruit);

    ASSERT_EQ(veryGoodFruit.y, 4);
    ASSERT_EQ(veryBadFruit.y, 7);
}

TEST(CollisionTest, CheckRegularFruitCollisionsTest) {
    Rectangle player {0, 0, 20, 20};
    Rectangle goodFruit {10, 10, 10, 10};
    Rectangle badFruit {20, 20, 10, 10};
    int score = 0;
    int fruitsCaught = 0;
    Sound bonus, damage, lostBonus;
    int screenWidth = 800;
    int screenHeight = 600;
    int randomGoodIndex = 0;
    int randomBadIndex = 0;

    collision::CheckRegularFruitCollisions(player, goodFruit, badFruit, score, fruitsCaught, bonus, damage, screenWidth, screenHeight, randomGoodIndex, randomBadIndex, lostBonus);

    ASSERT_EQ(score, 1);
    ASSERT_EQ(fruitsCaught, 1);
}

TEST(CollisionTest, CheckVeryGoodFruitCollisionsTest) {
    Rectangle player {0, 0, 20, 20};
    Rectangle veryGoodFruit {10, 10, 10, 10};
    int score = 0;
    int fruitsCaught = 0;
    Sound bonus, lostBonus;
    int screenHeight = 600;
    float veryGoodFruitTimer = 0.0f;
    int screenWidth = 800;
    float veryGoodFruitInterval = 15.0f;

    int randomGoodIndex = 0;
    collision::CheckVeryGoodFruitCollisions(player, veryGoodFruit, score, fruitsCaught, bonus, randomGoodIndex, lostBonus, screenHeight, veryGoodFruitTimer, screenWidth, veryGoodFruitInterval);


    ASSERT_EQ(score, 3);
    ASSERT_EQ(fruitsCaught, 1);

}

TEST(CollisionTest, CheckVeryBadFruitCollisionsTest) {
    Rectangle player {0, 0, 20, 20};
    Rectangle veryBadFruit {10, 10, 10, 10};
    Window window;
    int screenHeight = 600;
    int screenWidth = 800;
    int fruitsCaught = 0;

    collision::CheckVeryBadFruitCollisions(player, veryBadFruit, window, screenHeight, screenWidth, fruitsCaught);

    ASSERT_EQ(window.getScreen(), Window::LOSS);
}


