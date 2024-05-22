#include "raylib.h"
#include "../Scenes/scenes.h"
#include <vector>
#include "enemy.h"
#include <algorithm>

void ExamGame(Window &window) {

    struct Bullet {
        Rectangle rect;
        Vector2 speed;
    };

    std::vector<Bullet> bullets;
    Vector2 direction = { 0, -1 };
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 2.0f;

    Rectangle player = { 400, 300, 25, 25 };
    Enemy enemy = { 1,2,3,4,5,6};



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

        if (IsKeyPressed(KEY_SPACE)) {
            Bullet newBullet = { { player.x + player.width / 2, player.y, 5, 5 }, {direction.x * 5.0f, direction.y * 5.0f } };
            bullets.push_back(newBullet);
        }


        for (auto &bullet : bullets) {
            bullet.rect.x += bullet.speed.x;
            bullet.rect.y += bullet.speed.y;
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.rect.y < 0 || b.rect.y > 600 || b.rect.x < 0 || b.rect.x > 800; }), bullets.end());

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(player, BLUE);
        for (const auto &bullet : bullets) {
            DrawRectangleRec(bullet.rect, RED);
        }

        EndDrawing();
    }

    CloseWindow();

}
