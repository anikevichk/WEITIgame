#include "raylib.h"
#include "../../Scenes/scenes.h"

void Catch(Window &window) {
    const int screenWidth = 1600;
    const int screenHeight = 900;

    Rectangle catcher = { static_cast<float>(screenWidth / 2 - 40), static_cast<float>(screenHeight - 40), 80, 20 };
    Rectangle fruit = { static_cast<float>(GetRandomValue(0, screenWidth - 40)), 0, 40, 40 };

    int score = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_A)) {
            catcher.x -= 7;
        }
        if (IsKeyDown(KEY_D)) {
            catcher.x += 7;
        }

        fruit.y += 5;

        if (CheckCollisionRecs(catcher, fruit)) {
            score++;
            fruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            fruit.y = 0;
        }

        if (fruit.y > screenHeight) {
            fruit.x = static_cast<float>(GetRandomValue(0, screenWidth - 40));
            fruit.y = 0;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(catcher, BLUE);
        DrawRectangleRec(fruit, RED);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
}
