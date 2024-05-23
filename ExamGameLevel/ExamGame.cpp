#include "raylib.h"
#include "../Scenes/scenes.h"
#include <vector>
#include "enemy.h"
#include <algorithm>
#include <random>


int getRandom(int a, int b, int gapStart, int gapEnd) {           // method used to generate random coordinates of enemies
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);
    int random = dist(gen);


    if (random >= gapStart) {
        random += (gapEnd - gapStart);
    }
    return random;
}


void ExamGame(Window &window) {

    struct Bullet {
        Rectangle rect;
        Vector2 speed;
        bool hit = false;
    };

//    struct Cell {
//        std::vector<Enemy*> enemies;
//    };

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    Vector2 direction = { 0, -1 };

    int screenWidth = 1600;
    int screenHeight = 900;
    int playerHealth = 100;
    int bulletDamage = 25;
    int counter = 0;
    int gridSize = 100;
    float speed = 2.0f;
    float enemySpawnRate = 10.0f;
    float enemySpawnerTimer = 10.0f;
    float damageRate = 2.0f;
    float damageTimer = 2.0;

//    std::vector<std::vector<Cell>> grid(screenWidth / gridSize, std::vector<Cell>(screenHeight / gridSize));


    Rectangle player = { 400, 300, 25, 25 };
    Rectangle healthBar = { player.x-15, player.y - 20, 70, 5 };




    SetTargetFPS(60);

    while (!WindowShouldClose()) {

//        for (auto &enemy : enemies) {
//
//                int prevX = static_cast<int>(enemy.x) / gridSize;
//                int prevY = static_cast<int>(enemy.y) / gridSize;
//
//                enemy.moveToPlayer(player.x, player.y);
//
//            if (enemy.x >= 0 && enemy.x <= screenWidth && enemy.y >= 0 && enemy.y <= screenHeight) {
//                int newX = static_cast<int>(enemy.x) / gridSize;
//                int newY = static_cast<int>(enemy.y) / gridSize;
//
//                if (prevX != newX || prevY != newY) {
//
//                    auto &prevCell = grid[prevX][prevY];
//                    prevCell.enemies.erase(std::remove(prevCell.enemies.begin(), prevCell.enemies.end(), &enemy),
//                                           prevCell.enemies.end());
//                    grid[newX][newY].enemies.push_back(&enemy);
//                }
//            }
//        }

        if (IsKeyDown(KEY_W)) {
            if(player.y > 0) {
                player.y -= speed;
            }
            direction = { 0, -1 };
        }
        if (IsKeyDown(KEY_S)) {
            if(player.y < screenHeight-25) {
                player.y += speed;
            }
            direction = { 0, 1 };
        }
        if (IsKeyDown(KEY_A)) {
            if(player.x > 0) {
                player.x -= speed;
            }
            direction = { -1, 0 };
        };
        if (IsKeyDown(KEY_D)) {
            if (player.x < screenWidth - 25) {
                player.x += speed;
            }
            direction = { 1, 0 };
        }


        if (IsKeyPressed(KEY_SPACE)) {
            Bullet newBullet = { { player.x + player.width / 2, player.y + player.height / 2, 5, 5 }, {direction.x * 5.0f, direction.y * 5.0f } };
            bullets.push_back(newBullet);
        }

        for (auto &bullet : bullets) {
            bullet.rect.x += bullet.speed.x;
            bullet.rect.y += bullet.speed.y;
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [screenWidth, screenHeight](Bullet& b) {
            return b.rect.y < 0 ||
                    b.rect.y > screenHeight ||
                    b.rect.x < 0 ||
                    b.rect.x > screenWidth ||
                    b.hit; }), bullets.end());

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& enemy) {
            return enemy.GetHealth() <= 0;}), enemies.end());

        enemySpawnerTimer += GetFrameTime();
        if(enemySpawnerTimer >= enemySpawnRate) {
            enemySpawnerTimer = 0.0f;
            for (int i = 0; i < 30; i += 2) {
                enemies.emplace_back(getRandom(-100, screenWidth + 100, 0, screenWidth),
                                     getRandom(-100, screenHeight + 100, 0, screenHeight), 25, 30, 5, 25);
                enemies.emplace_back(GetRandomValue(0, screenWidth),
                                     getRandom(-100, screenHeight + 100, 0, screenHeight), 25, 30, 5, 25);

            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        healthBar.x = player.x - 25;
        healthBar.y = player.y -20;

        DrawRectangleRec(player, BLUE);
        DrawRectangleRec(healthBar, RED);

        for (const auto &bullet : bullets) {
            DrawRectangleRec(bullet.rect, RED);
        }

        damageTimer += GetFrameTime();

//        for (auto& bullet : bullets) {
//            int x = bullet.rect.x / gridSize;
//            int y = bullet.rect.y / gridSize;
//
//
//            for (int dx = -1; dx <= 1; ++dx) {
//                for (int dy = -1; dy <= 1; ++dy) {
//                    int newX = x + dx;
//                    int newY = y + dy;
//
//                    if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
//                        for (auto &enemy : grid[newX][newY].enemies) {
//                            if (CheckCollisionRecs(*enemy, bullet.rect)) {
//                                enemy->ReceiveDamage(bulletDamage);
//                                bullet.hit = true;
//                                ++counter;
//                            }
//                        }
//                    }
//                }
//            }
//        }

        for ( auto &enemy : enemies) {
            if (enemy.x >= 0 && enemy.x <= screenWidth && enemy.y >= 0 && enemy.y <= screenHeight) {
                for (auto &bullet: bullets) {
                    if (CheckCollisionRecs(enemy, bullet.rect)) {
                        enemy.ReceiveDamage(bulletDamage);
                        bullet.hit = true;
                        ++counter;
                    }

                }

                if (CheckCollisionRecs(enemy, player) && damageTimer >= damageRate) {
                    damageTimer = 0.0f;
                    playerHealth -= enemy.GetDamage();
                    healthBar.width -= 75 * enemy.GetDamage() / 100;
                }
            }

            enemy.moveToPlayer(player.x, player.y);

            DrawRectangleRec(enemy, RED);
        }

            if (playerHealth <= 0){
                window.setScreen(Window::LOSS);
                break;
            }

        if (counter >= 100){
            window.setScreen(Window::VICTORY);
            break;
        }

        DrawText(TextFormat("100/ %i", counter), screenWidth - 125, 0, 30, BLACK);


        EndDrawing();
    }


}
