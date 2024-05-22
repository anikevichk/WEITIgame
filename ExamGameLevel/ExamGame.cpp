#include "raylib.h"
#include "../Scenes/scenes.h"
#include <vector>
#include "enemy.h"
#include <algorithm>
#include <random>


int getRandom(int a, int b) {           // method used to generate random coordinates of enemies
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);
    int random = dist(gen);
    return random;
}


void ExamGame(Window &window) {

    struct Bullet {
        Rectangle rect;
        Vector2 speed;
    };

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    Vector2 direction = { 0, -1 };

    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 2.0f;
    int bulletDamage = 25;
    int i = 0;

    Rectangle player = { 400, 300, 25, 25 };
//    Enemy enemy = { 1,2,25,30,5,6};



    SetTargetFPS(60);

    while (!WindowShouldClose()) {

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

//        enemy.moveToPlayer(player.x, player.y);

        if (IsKeyPressed(KEY_SPACE)) {
            Bullet newBullet = { { player.x + player.width / 2, player.y, 5, 5 }, {direction.x * 5.0f, direction.y * 5.0f } };
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
                    b.rect.x > screenWidth; }), bullets.end());

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& enemy) {
            return enemy.GetHealth() <= 0;}), enemies.end());

        for(i ; i <10; ++i){
            enemies.emplace_back(getRandom(-100,0), getRandom(0,screenHeight), 25,30,5,6);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(player, BLUE);
//        DrawRectangleRec(enemy,RED);

        for (const auto &bullet : bullets) {
            DrawRectangleRec(bullet.rect, RED);
        }

        for ( auto &enemy : enemies) {
            for (auto& bullet : bullets) {
                if (CheckCollisionRecs(enemy, bullet.rect)) {
                    enemy.ReceiveDamage(bulletDamage);
                }
            }
            enemy.moveToPlayer(player.x, player.y);
            DrawRectangleRec(enemy, RED);
        }

        EndDrawing();
    }

    CloseWindow();

}
