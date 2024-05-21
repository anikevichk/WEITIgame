#include <cmath>
#include <random>
#include "raylib.h"
#include "level1.h"

void level1(Window &window) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(500, 2000);

    int counter = 0;
    int lastrandom = dist(gen);
    int screenWidth = 1600;
    int screenHeight = 900;
    bool isJumping = false;
    bool isClimbing = false;
    bool Climb = false;
    float jumpSpeed = 12.0f;
    float gravity = 0.4;
    int normalAlt = 75;
    float obstacleSpeed = 5.0f;
    bool loss = false;


    Texture2D playerTexture = LoadTexture("../src/player.png");
    Texture2D obstacleTexture = LoadTexture("../src/obstacle.png");
    Texture2D backgroundTexture = LoadTexture("../src/background.png");
    Texture2D floorTexture = LoadTexture("../src/floor.png");
    Texture2D serverTexture = LoadTexture("../src/server.png");



    Rectangle player = {50, screenHeight - 25, 10, 50};
    Rectangle obstacle = {screenWidth, screenHeight - 75, 50, 50};
    Rectangle floor1 = {0, screenHeight - 25, screenWidth, 25};
    Rectangle floor2 = {0, screenHeight - 300, screenWidth, 25};
    Rectangle floor3 = {0, screenHeight - 575, screenWidth, 25};


    const int numObstacles = 6;
    Rectangle obstacles[numObstacles] = {
            {screenWidth, screenHeight - 75, 50, 50},
            {screenWidth, screenHeight - 350, 50, 50},
            {screenWidth, screenHeight - 625, 50, 50},
            {screenWidth, screenHeight - 175, 50, 150},
            {screenWidth, screenHeight - 450, 50, 150},
            {screenWidth, screenHeight - 725, 50, 150}
    };

    for (int currentObstacle = 0; currentObstacle < numObstacles; currentObstacle++){
        int random;
        do {
        random = dist(gen);
        } while (abs(random-lastrandom) < 200);

        obstacles[currentObstacle].x = obstacles[currentObstacle].x + random ;
    }

    player.y = screenHeight - normalAlt;

    while (!WindowShouldClose()) {

        if (loss){
            window.setScreen(Window::LOSS);
            break;
        }

        int random;
        do {
            random = dist(gen);

        } while (abs(random-lastrandom) < 200);

//        int currentObstacle = rand() % numObstacles;
        for (int currentObstacle = 0; currentObstacle < numObstacles; currentObstacle++) {
            obstacles[currentObstacle].x -= obstacleSpeed;


            if (CheckCollisionRecs(player, obstacles[currentObstacle])) {

                obstacleSpeed = 0.0f;
                UnloadTexture(playerTexture);
                UnloadTexture(obstacleTexture);
                UnloadTexture(backgroundTexture);
                UnloadTexture(floorTexture);

                loss = true;
//                break;
            }


            if (obstacles[currentObstacle].x < 0) {
                obstacles[currentObstacle].x = screenWidth + random;
                counter ++;
            }

        }

        if (counter >= 50){
            window.setScreen(Window::VICTORY);
            obstacleSpeed = 0.0f;
            UnloadTexture(playerTexture);
            UnloadTexture(obstacleTexture);
            UnloadTexture(backgroundTexture);
            UnloadTexture(floorTexture);
            break;
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
        DrawTexture(serverTexture, obstacles[3].x - 45, obstacles[3].y - 50, WHITE);
        DrawTexture(serverTexture, obstacles[4].x - 45, obstacles[4].y - 50, WHITE);
        DrawTexture(serverTexture, obstacles[5].x - 45, obstacles[5].y - 50, WHITE);
        DrawText(TextFormat("50/ %i", counter), screenWidth - 125, 0,30,WHITE);

        EndDrawing();
    }


}
