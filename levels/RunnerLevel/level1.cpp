#include <cmath>
#include <random>
#include "raylib.h"
#include "../../Scenes/scenes.h"

int lastrandom = 0;
int getRandom() {           // method used to generate random coordinates of obstacles
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(500, 2000);


    int random;
    do {
        random = dist(gen);

    } while (abs(random - lastrandom) < 200);

    lastrandom = random;
    return random;
}

void level1(Window &window) {

    int counter = 0;
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
    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;


    Texture2D playerSprite = LoadTexture("../src/sprite.png");    //textures
    Texture2D obstacleTexture = LoadTexture("../src/levelRunner/obstacle.png");
    Texture2D backgroundTexture = LoadTexture("../src/levelRunner/background.png");
    Texture2D floorTexture = LoadTexture("../src/levelRunner/floor.png");
    Texture2D serverTexture = LoadTexture("../src/levelRunner/server.png");

    Rectangle frames[] = {                              //frames for player animation
            {0,  0, 66, 95},
            {73, 0, 66, 95}
    };


    Rectangle player = {50, static_cast<float>(screenHeight - 25), 10, 50};                             //hitboxes
    Rectangle floor1 = {0, static_cast<float>(screenHeight - 25), static_cast<float>(screenWidth), 25};
    Rectangle floor2 = {0, static_cast<float>(screenHeight - 300), static_cast<float>(screenWidth), 25};
    Rectangle floor3 = {0, static_cast<float>(screenHeight - 575), static_cast<float>(screenWidth), 25};


    const int numObstacles = 6;
    Rectangle obstacles[numObstacles] = {
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 75),  50, 50},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 350), 50, 50},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 625), 50, 50},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 175), 50, 150},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 450), 50, 150},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 725), 50, 150}
    };

    for (auto &obstacle: obstacles) {   //random generation of start postion of obstacles
        int random = getRandom();

        obstacle.x = obstacle.x + random;
    }

    player.y = screenHeight - normalAlt;        //set y coordinate of player

    while (!WindowShouldClose()) {

        if (loss) {                                     //check if loss flag was setted
            window.setScreen(Window::LOSS);
            break;
        }


        for (auto &obstacle: obstacles) {   //check all obstacles
            obstacle.x -= obstacleSpeed;


            if (CheckCollisionRecs(player, obstacle)) {     //check collisions betwet player and all obstacles

                obstacleSpeed = 0.0f;
                UnloadTexture(playerSprite);
                UnloadTexture(obstacleTexture);
                UnloadTexture(backgroundTexture);
                UnloadTexture(floorTexture);

                loss = true;
            }


            if (obstacle.x < 0) {                       // when obstacle reach end of the map, set new x coordinate
                int random = getRandom();
                obstacle.x = screenWidth + random;
                counter++;
            }

        }

        if (counter >= 50) {                            //check if reguired amount of point was reached
            window.setScreen(Window::VICTORY);
            obstacleSpeed = 0.0f;
            UnloadTexture(playerSprite);
            UnloadTexture(obstacleTexture);
            UnloadTexture(backgroundTexture);
            UnloadTexture(floorTexture);
            break;
        }

        if (IsKeyDown(KEY_SPACE) && !isJumping) {   //check space key, that used for jumping
            isJumping = true;
        }


        if (player.y != screenHeight - normalAlt && Climb) {    //jump animation when player chang floor
            player.y = screenHeight - normalAlt;
            isJumping = true;
        }


        if (isJumping) {            //jump
            player.y -= jumpSpeed;
            jumpSpeed -= gravity;
            if (player.y > screenHeight - normalAlt) {
                player.y = screenHeight - normalAlt;
                isJumping = false;
                jumpSpeed = 10.0f;
            }
        }


        if (IsKeyReleased(KEY_W)) {     // check if W key realeasd, that used to go upper floor
            Climb = false;
        }

        if (IsKeyDown(KEY_W) && !Climb) {   // check if W key pressed, change y, coordinate of player

            Climb = true;


            if (normalAlt >= 350 && normalAlt < 625) {
                normalAlt = 625;
            }

            if (normalAlt < 350) {
                normalAlt = 350;
            }
        }

        if (IsKeyReleased(KEY_S)) {    // check if W key realeasd, that used to go lower floor
            Climb = false;
        }

        if (IsKeyDown(KEY_S) && !Climb) {   // check if S key pressed, change y, coordinate of player

            Climb = true;

            if (normalAlt <= 350) {
                normalAlt = 75;
            }

            if (normalAlt > 350) {
                normalAlt = 350;
            }

        }

        frameTimer += GetFrameTime();   //frame changer
        if (frameTimer >= frameRate) {
            frameTimer = 0.0f;
            currentFrame++;

            if (currentFrame >= sizeof(frames) / sizeof(Rectangle)) {
                currentFrame = 0;
            }
        }


        BeginDrawing();
        //draw all objects
        ClearBackground(RAYWHITE);
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        DrawTexture(floorTexture, floor1.x, floor1.y, WHITE);
        DrawTexture(floorTexture, floor2.x, floor2.y, WHITE);
        DrawTexture(floorTexture, floor3.x, floor3.y, WHITE);
        DrawTextureRec(playerSprite, frames[currentFrame], (Vector2) {player.x - 45, player.y - 50}, WHITE);
        DrawTexture(obstacleTexture, obstacles[0].x - 45, obstacles[0].y - 50, WHITE);
        DrawTexture(obstacleTexture, obstacles[1].x - 45, obstacles[1].y - 50, WHITE);
        DrawTexture(obstacleTexture, obstacles[2].x - 45, obstacles[2].y - 50, WHITE);
        DrawTexture(serverTexture, obstacles[3].x - 45, obstacles[3].y - 50, WHITE);
        DrawTexture(serverTexture, obstacles[4].x - 45, obstacles[4].y - 50, WHITE);
        DrawTexture(serverTexture, obstacles[5].x - 45, obstacles[5].y - 50, WHITE);
        DrawText(TextFormat("50/ %i", counter), screenWidth - 125, 0, 30, WHITE);

        EndDrawing();
    }


}

