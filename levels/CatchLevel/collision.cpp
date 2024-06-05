#include "collision.h"

// Function to move special fruits (veryGoodFruit and veryBadFruit)
void collision::MoveSpecialFruits(Rectangle& veryGoodFruit, Rectangle& veryBadFruit) {
    // Move veryGoodFruit downwards
    if (veryGoodFruit.y > -40) {
        veryGoodFruit.y += 10;
    }
    // Move veryBadFruit downwards
    if (veryBadFruit.y > -40) {
        veryBadFruit.y += 7;
    }
}

// Function to check collisions with regular fruits (goodFruit and badFruit)
void collision::CheckRegularFruitCollisions(Rectangle& player, Rectangle& goodFruit, Rectangle& badFruit,
                                            int& score, int& fruitsCaught, Sound& bonus, Sound& damage,
                                            int& screenWidth, int& screenHeight,
                                            int& randomGoodIndex, int& randomBadIndex, Sound& lostBonus) {
    // Check collision with goodFruit
    if (CheckCollisionRecs(player, goodFruit)) {
        PlaySound(bonus);
        score++;
        fruitsCaught++;
        goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        goodFruit.y = 0;
        randomGoodIndex = GetRandomValue(0, 3);
    }

    // Check collision with badFruit
    if (CheckCollisionRecs(player, badFruit)) {
        PlaySound(damage);
        score--;
        badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        badFruit.y = 0;
        randomBadIndex = GetRandomValue(0, 2);
    }

    // Check if goodFruit is out of screen
    if (goodFruit.y > screenHeight) {
        PlaySound(lostBonus);
        score--;
        goodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        goodFruit.y = 0;
        randomGoodIndex = GetRandomValue(0, 3);
    }

    // Check if badFruit is out of screen
    if (badFruit.y > screenHeight) {
        badFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        badFruit.y = 0;
        randomBadIndex = GetRandomValue(0, 2);
    }
}

// Function to check collisions with veryGoodFruit
void collision::CheckVeryGoodFruitCollisions(Rectangle& player, Rectangle& veryGoodFruit,
                                             int& score, int& fruitsCaught, Sound& bonus,
                                             int& randomGoodIndex, Sound& lostBonus, int screenHeight,
                                             float& veryGoodFruitTimer, int& screenWidth, float& veryGoodFruitInterval) {
    // Check collision with veryGoodFruit
    if (CheckCollisionRecs(player, veryGoodFruit)) {
        PlaySound(bonus);
        score += 3;
        fruitsCaught++;
        veryGoodFruit.x = -40;
        veryGoodFruit.y = -40;
    }

    // Check if veryGoodFruit is out of screen
    if (veryGoodFruit.y > screenHeight) {
        PlaySound(lostBonus);
        score--;
        veryGoodFruit.x = -40;
        veryGoodFruit.y = -40;
    }

    // Reset veryGoodFruit position after certain interval
    if (veryGoodFruitTimer >= veryGoodFruitInterval) {
        veryGoodFruitTimer = 0.0f;
        veryGoodFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        veryGoodFruit.y = 0;
    }
}

// Function to check collisions with veryBadFruit
void collision::CheckVeryBadFruitCollisions(Rectangle& player, Rectangle& veryBadFruit, Window& window, int& screenHeight, int& screenWidth, int& fruitsCaught) {

    // Check if veryBadFruit is out of screen
    if (veryBadFruit.y > screenHeight) {
        veryBadFruit.x = -40;
        veryBadFruit.y = -40;
    }

    // Reset veryBadFruit position after every 5 caught fruits
    if (fruitsCaught > 0 && fruitsCaught % 5 == 0) {
        fruitsCaught = 0;
        veryBadFruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
        veryBadFruit.y = 0;
    }
}

// Function to check all collisions
void collision::CheckCollisions(Rectangle& player, Rectangle& goodFruit, Rectangle& badFruit, Rectangle& veryGoodFruit, Rectangle& veryBadFruit,
                                int& score, int& fruitsCaught, Sound& bonus, Sound& lostBonus, Sound& damage,
                                int& screenWidth, int& screenHeight, Window& window, int& randomGoodIndex,
                                int& randomBadIndex, float& veryGoodFruitTimer) {
    // Interval for resetting veryGoodFruit position
    float veryGoodFruitInterval = 15.0f;

    // Move special fruits
    MoveSpecialFruits(veryGoodFruit, veryBadFruit);

    // Check collisions with regular fruits
    CheckRegularFruitCollisions(player, goodFruit, badFruit, score, fruitsCaught, bonus, damage, screenWidth, screenHeight, randomGoodIndex, randomBadIndex, lostBonus);

    // Check collisions with veryGoodFruit
    CheckVeryGoodFruitCollisions(player, veryGoodFruit, score, fruitsCaught, bonus, randomGoodIndex, lostBonus, screenHeight, veryGoodFruitTimer, screenWidth, veryGoodFruitInterval);

    // Check collisions with veryBadFruit
    CheckVeryBadFruitCollisions(player, veryBadFruit, window, screenHeight, screenWidth, fruitsCaught);
}
