#include "raylib.h"
#include "Structs.h"
#ifndef UNTITLED_LEVELMANAGER_H
#define UNTITLED_LEVELMANAGER_H


class LevelManager {
    int counter = 0;
    int screenWidth = 1600;
    int screenHeight = 900;
    float obstacleSpeed = 5.0f;
    bool loss = false;


    Texture2D floorTexture = LoadTexture("../src/levelRunner/floor.png");
    Sound JumpEffect = LoadSound("../src/sounds/jumpEffect.mp3");
    Texture2D obstacleTexture = LoadTexture("../src/levelRunner/obstacle.png");
    Texture2D serverTexture = LoadTexture("../src/levelRunner/server.png");

    Player player = {50, static_cast<float>(screenHeight - 25), 10, 50};                             //hitboxes
    Rectangle floor1 = {0, static_cast<float>(screenHeight - 25), static_cast<float>(screenWidth), 25};
    Rectangle floor2 = {0, static_cast<float>(screenHeight - 300), static_cast<float>(screenWidth), 25};
    Rectangle floor3 = {0, static_cast<float>(screenHeight - 575), static_cast<float>(screenWidth), 25};

     Obstacle obstacles[6] = {
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 75),  50, 50},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 350), 50, 50},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 625), 50, 50},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 175), 50, 150},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 450), 50, 150},
            {static_cast<float>(screenWidth), static_cast<float>(screenHeight - 725), 50, 150}
    };

public:

    bool isLoss() const;

    void setLoss(bool loss);

    void InitLevel();
    void CheckObstacle();
    bool isVictory();
    void CheckJump();
    void CheckClimb();
    void UpdateFrame();

    int getCounter() const;

    const Texture2D &getFloorTexture() const;

    const Rectangle &getFloor1() const;

    const Rectangle &getFloor2() const;

    const Rectangle &getFloor3() const;

    const Texture2D &getObstacleTexture() const;

    const Texture2D &getServerTexture() const;

    const Player &getPlayer() const;

    const Obstacle &getObstacles(int inedx) const;

    int getScreenWidth() const;

};


#endif //UNTITLED_LEVELMANAGER_H
