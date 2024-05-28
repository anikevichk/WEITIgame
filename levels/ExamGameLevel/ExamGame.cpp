#include "raylib.h"
#include "../../Scenes/scenes.h"
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
        float rotate;
        bool hit = false;
        int texture = GetRandomValue(0,9);
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

    Texture2D playerSprite = LoadTexture("../src/sprite.png");
    Texture2D hotdogTexture = LoadTexture("../src/hotdog.png");
    Texture2D BulletsTexture = LoadTexture("../src/levelExam/Bullets.png");
    Texture2D EnemiesTexture = LoadTexture("../src/levelExam/enemies.png");
    Texture2D BackgroundTexture = LoadTexture("../src/levelExam/Background.png");
    Sound ExamSound = LoadSound("../src/sounds/Exam.mp3");
    Sound ThrowEffect = LoadSound("../src/sounds/throwEffect.mp3");




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

    Rectangle EnemyTextures[] = {
            {0,0,46, 50},
            {47,0,40, 50},
            {87,0,47, 50},
            {134, 0, 40,50}
    };

    Rectangle BulletsTextures[] = {
            {0,0,10, 3},
            {10,0,10, 3},
            {20,0,10, 3},
            {30,0,10, 3},
            {40,0,10, 3},
            {50,0,10, 3},
            {60,0,10, 3},
            {70,0,10, 3},
            {80,0,10, 3},
            {90,0,10, 3},
    };

    Rectangle player = { 800, 450, 50, 95 };
    Rectangle healthBar = { player.x-15, player.y - 20, 70, 5 };
    Rectangle hotdog = {-30, -30, 25, 25 };




    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        frameTimer += GetFrameTime();   //update vairabels needed to next frame;
        hotDogTimer += GetFrameTime();
        enemySpawnerTimer += GetFrameTime();
        damageTimer += GetFrameTime();
        healthBar.x = player.x - 12;
        healthBar.y = player.y - 30;

        if (!IsSoundPlaying(ExamSound))
        {
            PlaySound(ExamSound);
        }

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
            PlaySound(ThrowEffect);
            float rotate;
            if( direction.x == 1) rotate = 180.0f;
            if( direction.x == -1) rotate = 0.0f;
            if( direction.y == 1) rotate = 270.0f;
            if( direction.y == -1) rotate = 90.0f;

            Bullet newBullet = { { player.x + player.width / 2 + 12, player.y + player.height / 2+20, 5, 5 }, {direction.x * 5.0f, direction.y * 5.0f }, rotate };
            bullets.push_back(newBullet);
        }

        if (playerHealth <= 0){
            window.setScreen(Window::LOSS);
            StopSound(ExamSound);
            UnloadSound(ExamSound);
            UnloadSound(ThrowEffect);
            UnloadTexture(playerSprite);
            UnloadTexture(EnemiesTexture);
            UnloadTexture(BulletsTexture);
            UnloadTexture(BackgroundTexture);
            break;
        }

        if (counter >= 100){
            window.setScreen(Window::VICTORY);
            StopSound(ExamSound);
            UnloadSound(ExamSound);
            UnloadSound(ThrowEffect);
            UnloadTexture(playerSprite);
            UnloadTexture(EnemiesTexture);
            UnloadTexture(BulletsTexture);
            UnloadTexture(BackgroundTexture);
            break;
        }


        if (frameTimer >= frameRate) {
            frameTimer = 0.0f;
            if(isKeyPressed) {
                currentFrame++;

                if (currentFrame >= FrameSize) {
                    currentFrame = 0;
                }
            } else currentFrame = 0;
        }

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

        if(enemySpawnerTimer >= enemySpawnRate) {
            enemySpawnerTimer = 0.0f;
            for (int i = 0; i < 30; i += 2) {
                enemies.emplace_back(getRandom(-100, screenWidth + 100, 0, screenWidth),
                                     getRandom(-100, screenHeight + 100, 0, screenHeight), 30, 50, 5, 25);
                enemies.emplace_back(GetRandomValue(0, screenWidth),
                                     getRandom(-100, screenHeight + 100, 0, screenHeight), 30, 50, 5, 25);

            }
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [screenWidth, screenHeight](Bullet& b) {
            return b.rect.y < 0 ||
                   b.rect.y > screenHeight ||
                   b.rect.x < 0 ||
                   b.rect.x > screenWidth ||
                   b.hit; }), bullets.end());

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& enemy) {
            return enemy.GetHealth() <= 0;}), enemies.end());

        for (auto &bullet : bullets) {
            bullet.rect.x += bullet.speed.x;
            bullet.rect.y += bullet.speed.y;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(BackgroundTexture, 0, 0, WHITE);



        for (const auto &bullet : bullets) {
            DrawTexturePro(BulletsTexture,BulletsTextures[bullet.texture],{bullet.rect.x, bullet.rect.y, 20,6},Vector2 {0,0}, bullet.rotate, WHITE);
        }



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
                }
            }

            enemy.moveToPlayer(player.x + player.width/2, player.y + player.height/2);

            DrawTextureRec(EnemiesTexture, EnemyTextures[enemy.GetTexture()], (Vector2) {enemy.x, enemy.y }, WHITE);

        }


        healthBar.width =static_cast<int>( 70.0f * (static_cast<float>(playerHealth)/100.0f));

        DrawText(TextFormat("100/ %i", counter), screenWidth - 125, 0, 30, BLACK);
        DrawTextureRec(playerSprite, currentFrames[currentFrame], (Vector2) {player.x - 15, player.y }, WHITE);
        DrawTexture(hotdogTexture, hotdog.x, hotdog.y, WHITE );
        DrawRectangleRec(healthBar, RED);





        EndDrawing();
    }


}
