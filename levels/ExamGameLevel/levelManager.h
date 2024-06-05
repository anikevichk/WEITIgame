#include "raylib.h"
#include "enemy.h"
#include "Player.h"
#include "../../Scenes/scenes.h"
#include <vector>
#include <cstring>
#ifndef UNTITLED_LEVELMANAGER_H
#define UNTITLED_LEVELMANAGER_H

struct Bullet {
    Rectangle rect;
    Vector2 speed;
    float rotate;
    int Damage = 25;
    bool hit = false;
    int texture = GetRandomValue(0,9);
    Rectangle Textures[10] = {
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
};
struct HealthBar:Rectangle {
    HealthBar(float x, float y, int width, int height){
        this-> x = x;
        this -> y = y;
        this->width = width;
        this->height = height;
    }
};
struct Hotdog:Rectangle{
    Hotdog(float x, float y, int width, int height){
        this-> x = x;
        this -> y = y;
        this->width = width;
        this->height = height;
    }
    Texture2D hotdogTexture = LoadTexture("../src/hotdog.png");
    float hotDogTimer = 10.0f;
    float hotDogRate = 20.0f;
};

class levelManager {
    bool isKeyPressed = false;

    int counter = 0;
    int screenWidth = 1600;
    int screenHeight = 900;
    float enemySpawnRate = 10.0f;
    float enemySpawnerTimer = 10.0f;

    Window& window;
    Vector2 direction = { 0, -1 };
    Player player = { 800, 450, 50, 95, 100 };
    HealthBar healthBar = { player.x-15, player.y - 20, 70, 5 };
    Hotdog hotdog = {-30, -30, 25, 25 };
    Sound ThrowEffect = LoadSound("../src/sounds/throwEffect.mp3");
    Texture2D BulletsTexture = LoadTexture("../src/levelExam/Bullets.png");
    Texture2D EnemiesTexture = LoadTexture("../src/levelExam/enemies.png");
public:
    Sound speaking1 = LoadSound("../src/sounds/voice1.mp3");
    Sound speaking2 = LoadSound("../src/sounds/voice2.mp3");

    const char* text1 = "It's exam time! You have to write 'couple' tests \n\n Don't worry, there aren't many of them.\n\n The only food that helps you survive is hotdogs.";
    const char* text2 = "Use W,A,S,D to move. And a space to throw a pencil.\n\n This is your only option to survive!";

    int textLength1 = strlen(text1);
    int currentLength1 = 0;
    int framesCounter1 = 0;

    int textLength2 = strlen(text2);
    int currentLength2 = 0;
    int framesCounter2 = 0;

    float letterDelay = 1;


    bool DialogueWindow1 = true;
    bool DialogueWindow2 = false;
    bool isRightHalf = false;
    explicit levelManager(Window& window);
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    bool End = false;
    void Update();
    void CheckButtons();
    void CheckEnd();
    void UpdateplayerSprite();
    void UpdateHotdog();
    void UpdateEnemy();
    void UpdateBullets();
    const Texture2D &getEnemiesTexture() const;
    const Texture2D &getBulletsTexture() const;
    int getCounter() const;
    int getScreenWidth() const;
    int getScreenHeight() const;
    const Hotdog &getHotdog() const;
    const HealthBar &getHealthBar() const;
    const Player &getPlayer() const;
};


#endif //UNTITLED_LEVELMANAGER_H
