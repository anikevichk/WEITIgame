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
//    int gridSize = 100;
    int FrameSize;
    float speed = 2.0f;
    float enemySpawnRate = 10.0f;
    float enemySpawnerTimer = 10.0f;
    float damageRate = 2.0f;
    float damageTimer = 2.0;
    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;
    float hotDogTimer = 10.0f;
    float hotDogRate = 20.0f;

    Texture2D playerSprite = LoadTexture("../src/levelExam/playerSprite.png");
    Texture2D hotdogTexture = LoadTexture("../src/levelExam/hotdog.png");


//    std::vector<std::vector<Cell>> grid(screenWidth / gridSize, std::vector<Cell>(screenHeight / gridSize));

    Rectangle runRightFrames[] = {                              //frames for player animation
            {0,  0, 70, 95},
            {73, 0, 70, 95}
    };

    Rectangle runLeftFrames[] = {                              //frames for player animation
            {0,  104, 70, 95},
            {73, 104, 70, 95}
    };

    Rectangle runBackFrames[] = {                              //frames for player animation
            {0,  208, 73, 95},
            {80,  208, 73, 95},
            {160,  208, 73, 95}

    };

    Rectangle runForwardFrames[] = {                              //frames for player animation
            {0,  312, 73, 95},
            {80,  312, 73, 95},
            {160,  312, 73, 95}


    };

    Rectangle* currentFrames = runRightFrames;

    Rectangle player = { 800, 450, 50, 95 };
    Rectangle healthBar = { player.x-15, player.y - 20, 70, 5 };
    Rectangle hotdog = {-30, -30, 25, 25 };




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

            currentFrames = runForwardFrames;
            FrameSize = 3;
            isKeyPressed = true;
        }
        else if (IsKeyDown(KEY_S)) {
            if(player.y < screenHeight-25) {
                player.y += speed;
            }
            direction = { 0, 1 };

            currentFrames = runBackFrames;
            FrameSize = 3;
            isKeyPressed = true;

        }
        else if (IsKeyDown(KEY_A)) {
            if(player.x > 0) {
                player.x -= speed;
            }
            direction = { -1, 0 };

            currentFrames = runLeftFrames;
            FrameSize = 2;
            isKeyPressed = true;

        }
        else if (IsKeyDown(KEY_D)) {
            if (player.x < screenWidth - 25) {
                player.x += speed;
            }
            direction = { 1, 0 };

            currentFrames = runRightFrames;
            FrameSize = 2;
            isKeyPressed = true;

        } else isKeyPressed = false;


        if (IsKeyPressed(KEY_SPACE)) {
            Bullet newBullet = { { player.x + player.width / 2 + 12, player.y + player.height / 2+20, 5, 5 }, {direction.x * 5.0f, direction.y * 5.0f } };
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

        healthBar.x = player.x - 45;
        healthBar.y = player.y - 65;



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
//                    healthBar.width -= 75 * enemy.GetDamage() / 100;
                }
            }

            enemy.moveToPlayer(player.x + player.width/2, player.y + player.height/2);

            DrawRectangleRec(enemy, RED);
        }

            if (playerHealth <= 0){
                window.setScreen(Window::LOSS);
                UnloadTexture(playerSprite);
                break;
            }

        if (counter >= 100){
            window.setScreen(Window::VICTORY);
            UnloadTexture(playerSprite);
            break;
        }

        frameTimer += GetFrameTime();   //frame changer
        if (frameTimer >= frameRate) {
            frameTimer = 0.0f;
            if(isKeyPressed) {
                currentFrame++;

                if (currentFrame >= FrameSize) {
                    currentFrame = 0;
                }
            } else currentFrame = 0;
        }

        hotDogTimer += GetFrameTime();
        if (hotDogTimer >= hotDogRate){
            hotDogTimer = 0.0f;
            hotdog.x = GetRandomValue(0, screenWidth);
            hotdog.y = GetRandomValue(0, screenHeight);
        }

        if(CheckCollisionRecs(hotdog, player)){
            playerHealth += 25;
            hotdog.x = -30;
            hotdog.y = -30;
        }
;
        healthBar.width =static_cast<int>( 70.0f * (static_cast<float>(playerHealth)/100.0f));

        DrawText(TextFormat("100/ %i", counter), screenWidth - 125, 0, 30, BLACK);
//        DrawRectangleRec(player, BLUE);
        DrawTextureRec(playerSprite, currentFrames[currentFrame], (Vector2) {player.x - 15, player.y }, WHITE);
        DrawTexture(hotdogTexture, hotdog.x, hotdog.y, WHITE );
        DrawRectangleRec(healthBar, RED);





        EndDrawing();
    }


}
