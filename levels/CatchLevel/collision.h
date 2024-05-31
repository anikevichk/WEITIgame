#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"
#include "../../Scenes/scenes.h"

class collision {
public:
    static void MoveSpecialFruits(Rectangle& veryGoodFruit, Rectangle& veryBadFruit);

    static void CheckRegularFruitCollisions(Rectangle& player, Rectangle& goodFruit, Rectangle& badFruit,
                                            int& score, int& fruitsCaught, Sound& bonus, Sound& damage,
                                            int& screenWidth, int& screenHeight,
                                            int& randomGoodIndex, int& randomBadIndex, Sound& lostBonus);

    static void CheckVeryGoodFruitCollisions(Rectangle& player, Rectangle& veryGoodFruit,
                                             int& score, int& fruitsCaught, Sound& bonus,
                                             int& randomGoodIndex, Sound& lostBonus, int screenHeight,
                                             float& veryGoodFruitTimer, int& screenWidth, float& veryGoodFruitInterval);

    static void CheckVeryBadFruitCollisions(Rectangle& player, Rectangle& veryBadFruit, Window& window, int& screenHeight, int& screenWidth, int& fruitsCaught);

    static void CheckCollisions(Rectangle& player, Rectangle& goodFruit, Rectangle& badFruit, Rectangle& veryGoodFruit, Rectangle& veryBadFruit,
                                int& score, int& fruitsCaught, Sound& bonus, Sound& lostBonus, Sound& damage,
                                int& screenWidth, int& screenHeight, Window& window, int& randomGoodIndex,
                                int& randomBadIndex, float& veryGoodFruitTimer);
};

#endif // COLLISION_H