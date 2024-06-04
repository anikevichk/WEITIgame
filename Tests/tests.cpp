#include "gtest/gtest.h"
#include "../levels/CatchLevel/collision.h"

TEST(CollisionTest, MoveSpecialFruitsTest) {
    Rectangle veryGoodFruit {0, 0, 10, 10};
    Rectangle veryBadFruit {0, 0, 10, 10};

    collision::MoveSpecialFruits(veryGoodFruit, veryBadFruit);

    ASSERT_EQ(veryGoodFruit.y, 4);
    ASSERT_EQ(veryBadFruit.y, 7);
}