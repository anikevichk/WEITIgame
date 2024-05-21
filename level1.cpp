#include <cstdlib>
#include "raylib.h"
#include "level1.h"

void level1(Window &window) {

    int screenWidth = 1600;
    int screenHeight = 900;
    bool isJumping = false;
    bool isClimbing = false;
    bool Climb = false;
    float jumpSpeed = 12.0f;
    float gravity = 0.4;
    int normalAlt = 75;
    float obstacleSpeed = 5.0f;


    Texture2D playerTexture = LoadTexture("../src/player.png");
    Texture2D obstacleTexture = LoadTexture("../src/obstacle.png");
    Texture2D backgroundTexture = LoadTexture("../src/background.png");
    Texture2D floorTexture = LoadTexture("../src/floor.png");


    Rectangle player = {50, screenHeight - 25, 10, 50};
    Rectangle obstacle = {screenWidth, screenHeight - 75, 50, 50};
    Rectangle floor1 = {0, screenHeight - 25, screenWidth, 25};
    Rectangle floor2 = {0, screenHeight - 300, screenWidth, 25};
    Rectangle floor3 = {0, screenHeight - 575, screenWidth, 25};


    const int numObstacles = 3;
    Rectangle obstacles[numObstacles] = {
            {screenWidth, screenHeight - 75, 50, 50},
            {screenWidth, screenHeight - 350, 50, 50},
            {screenWidth, screenHeight - 625, 50, 50}
    };


    player.y = screenHeight - normalAlt;

    while (!WindowShouldClose()) {

        int currentObstacle = rand() % numObstacles;

        obstacles[currentObstacle].x -= obstacleSpeed;


        if (CheckCollisionRecs(player, obstacles[currentObstacle])) {

            obstacleSpeed = 0.0f;
            window.setScreen(Window::Menu);
            UnloadTexture(playerTexture);
            UnloadTexture(obstacleTexture);
            UnloadTexture(backgroundTexture);
            UnloadTexture(floorTexture);

            break;
        }


        if (obstacles[currentObstacle].x < 0) {
            obstacles[currentObstacle].x = screenWidth;
        }


        if (IsKeyDown(KEY_SPACE) && !isJumping) {
            isJumping = true;
        }


        if (player.y != screenHeight - normalAlt && Climb) {
            player.y = screenHeight - normalAlt;
            isJumping = true;

        }


        if (isJumping) {
            player.y -= jumpSpeed;
            jumpSpeed -= gravity;
            if (player.y > screenHeight - normalAlt) {
                player.y = screenHeight - normalAlt;
                isJumping = false;
                jumpSpeed = 10.0f;
            }
        }


        if (IsKeyReleased(KEY_W)) {
            Climb = false;
        }

        if (IsKeyDown(KEY_W) && !Climb) {

            Climb = true;


            if (normalAlt >= 350 && normalAlt < 625) {
                normalAlt = 625;
            }

            if (normalAlt < 350) {
                normalAlt = 350;
            }
        }

        if (IsKeyReleased(KEY_S)) {
            Climb = false;
        }

        if (IsKeyDown(KEY_S) && !Climb) {

            Climb = true;

            if (normalAlt <= 350) {
                normalAlt = 75;
            }

            if (normalAlt > 350 && normalAlt <= 625) {
                normalAlt = 350;
            }

        }


        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        DrawTexture(floorTexture, floor1.x, floor1.y, WHITE);
        DrawTexture(floorTexture, floor2.x, floor2.y, WHITE);
        DrawTexture(floorTexture, floor3.x, floor3.y, WHITE);
        DrawTexture(playerTexture, player.x - 45, player.y - 50, WHITE);
        DrawTexture(obstacleTexture, obstacles[0].x - 45, obstacles[0].y - 50, WHITE);
        DrawTexture(obstacleTexture, obstacles[1].x - 45, obstacles[1].y - 50, WHITE);
        DrawTexture(obstacleTexture, obstacles[2].x - 45, obstacles[2].y - 50, WHITE);

        EndDrawing();
    }


}
