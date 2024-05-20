#include "raylib.h"
#include "level1.h"
 void level1(Window& window)
{

    int screenWidth = 1600;
    int screenHeight = 900;
//    InitWindow(screenWidth, screenHeight, "EscapeFromWEITI");

Texture2D playerTexture = LoadTexture("C:\\Users\\matve\\CLionProjects\\Game\\src\\tex100.png");


    Rectangle player = { 50, screenHeight - 50, 10, 50 };
    bool isJumping = false;
    float jumpSpeed = 12.0f;
    float gravity =0.4;


    Rectangle obstacle = { screenWidth, screenHeight - 100, 50, 50 };


    float obstacleSpeed = 5.0f;

//    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        obstacle.x -= obstacleSpeed;


        if (CheckCollisionRecs(player, obstacle))
        {

            obstacleSpeed = 0.0f;
            window.setScreen(Window::Menu);
            UnloadTexture(playerTexture);
            break;
        }


        if (obstacle.x < 0)
        {
            obstacle.x = screenWidth;
        }


        if (IsKeyDown(KEY_SPACE) && !isJumping)
        {
            isJumping = true;
        }

        if (isJumping)
        {
            player.y -= jumpSpeed;
            jumpSpeed -= gravity;
        }

        if (player.y > screenHeight - 100)
        {
            player.y = screenHeight - 100;
            isJumping = false;
            jumpSpeed = 10.0f;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

//        DrawRectangleRec(player, BLUE); // Відображення гравця
        DrawTexture(playerTexture, player.x-45, player.y-50, WHITE);
        DrawRectangleRec(obstacle, RED); // Відображення перешкоди

        EndDrawing();
    }



}
