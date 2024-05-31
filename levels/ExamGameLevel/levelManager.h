#include "raylib.h"
#include "enemy.h"
#include "Player.h"
#include "../../Scenes/scenes.h"
#include <vector>
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
    levelManager(Window& window);
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
    const Hotdog &getHotdog() const;
    const HealthBar &getHealthBar() const;
    const Player &getPlayer() const;
};


#endif //UNTITLED_LEVELMANAGER_H
