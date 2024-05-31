#include "collision.h"

void collision::MoveSpecialFruits(Rectangle& veryGoodFruit, Rectangle& veryBadFruit) {
    if (veryGoodFruit.y > -40) {
        veryGoodFruit.y += 4;
    }
    if (veryBadFruit.y > -40) {
        veryBadFruit.y += 7;
    }
}
void collision::CheckRegularFruitCollisions(Rectangle& player, Rectangle& goodFruit, Rectangle& badFruit,
                                            int& score, int& fruitsCaught, Sound& bonus, Sound& damage,
                                            int& screenWidth, int& screenHeight,
                                            int& randomGoodIndex, int& randomBadIndex, Sound& lostBonus) {
    if (CheckCollisionRecs(player, goodFruit)) {
        PlaySound(bonus);
        score++;
        fruitsCaught++;
        goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        goodFruit.y = 0;
        randomGoodIndex = GetRandomValue(0, 3);
    }

    if (CheckCollisionRecs(player, badFruit)) {
        PlaySound(damage);
        score--;
        badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        badFruit.y = 0;
        randomBadIndex = GetRandomValue(0, 2);
    }

    if (goodFruit.y > screenHeight) {
        PlaySound(lostBonus);
        score--;
        goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        goodFruit.y = 0;
        randomGoodIndex = GetRandomValue(0, 3);
    }

    if (badFruit.y > screenHeight) {
        badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        badFruit.y = 0;
        randomBadIndex = GetRandomValue(0, 2);
    }
}

void collision::CheckVeryGoodFruitCollisions(Rectangle& player, Rectangle& veryGoodFruit,
                                             int& score, int& fruitsCaught, Sound& bonus,
                                             int& randomGoodIndex, Sound& lostBonus, int screenHeight,
                                             float& veryGoodFruitTimer, int& screenWidth, float& veryGoodFruitInterval) {
    if (CheckCollisionRecs(player, veryGoodFruit)) {
        PlaySound(bonus);
        score += 3;
        fruitsCaught++;
        veryGoodFruit.x = -40;
        veryGoodFruit.y = -40;
    }

    if (veryGoodFruit.y > screenHeight) {
        PlaySound(lostBonus);
        score--;
        veryGoodFruit.x = -40;
        veryGoodFruit.y = -40;
    }

    if (veryGoodFruitTimer >= veryGoodFruitInterval) {
        veryGoodFruitTimer = 0.0f;
        veryGoodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        veryGoodFruit.y = 0;
    }

}

void collision::CheckVeryBadFruitCollisions(Rectangle& player, Rectangle& veryBadFruit, Window& window, int& screenHeight, int& screenWidth, int& fruitsCaught) {
    if (veryBadFruit.y > -40 && CheckCollisionRecs(player, veryBadFruit)) {
        window.setScreen(Window::LOSS);
        return;
    }

    if (veryBadFruit.y > screenHeight) {
        veryBadFruit.x = -40;
        veryBadFruit.y = -40;
    }

    if (fruitsCaught > 0 && fruitsCaught % 5 == 0) {
        fruitsCaught = 0;
        veryBadFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        veryBadFruit.y = 0;
    }


}

void collision::CheckCollisions(Rectangle& player, Rectangle& goodFruit, Rectangle& badFruit, Rectangle& veryGoodFruit, Rectangle& veryBadFruit,
                                int& score, int& fruitsCaught, Sound& bonus, Sound& lostBonus, Sound& damage,
                                int& screenWidth, int& screenHeight, Window& window, int& randomGoodIndex,
                                int& randomBadIndex, float& veryGoodFruitTimer) {
    float veryGoodFruitInterval = 15.0f;

    MoveSpecialFruits(veryGoodFruit, veryBadFruit);

    CheckRegularFruitCollisions(player, goodFruit, badFruit, score, fruitsCaught, bonus, damage, screenWidth, screenHeight, randomGoodIndex, randomBadIndex, lostBonus);

    CheckVeryGoodFruitCollisions(player, veryGoodFruit, score, fruitsCaught, bonus, randomGoodIndex,lostBonus, screenHeight, veryGoodFruitTimer, screenWidth, veryGoodFruitInterval);

    CheckVeryBadFruitCollisions(player, veryBadFruit, window, screenHeight, screenWidth, fruitsCaught);
}