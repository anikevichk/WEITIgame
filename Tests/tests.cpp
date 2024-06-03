#include "../levels/RunnerLevel/LevelManager.h"
#include <gtest/gtest.h>


TEST(LevelManagerTest, IsLossInitiallyFalse) {
    LevelManager levelManager;
ASSERT_EQ(levelManager.getCounter(),0);
}
