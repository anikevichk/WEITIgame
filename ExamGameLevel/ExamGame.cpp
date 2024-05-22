#include "../cmake-build-debug/vcpkg_installed/x64-windows/include/raylib.h"
#include "../Scenes/scenes.h"
#include <vector>
#include <iostream>
#include <algorithm>

void ExamGame(Window &window) {

    struct Bullet {
        Rectangle rect;
        Vector2 speed;
    };

    std::vector<Bullet> bullets;
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 2.0f;

    Rectangle player = { 400, 300, 25, 25 };




    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_W)) {
            if(player.y > 0) {
                player.y -= speed;
            }
        }
        if (IsKeyDown(KEY_S)) {
            if(player.y < screenHeight-25) {
                player.y += speed;
            }
        }
        if (IsKeyDown(KEY_A)) {
            if(player.x > 0) {
                player.x -= speed;
            }
        };
        if (IsKeyDown(KEY_D)) {
            if (player.x < screenWidth - 25) {
                player.x += speed;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            Bullet newBullet = { { player.x + player.width / 2, player.y, 5, 10 }, { 0, -5.0f } };
            bullets.push_back(newBullet);
        }


        for (auto &bullet : bullets) {
            bullet.rect.y += bullet.speed.y;
            if(bullet.rect.y < 0){
            }
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),  [](Bullet &b){ return b.rect.y < 0; }), bullets.end());

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
