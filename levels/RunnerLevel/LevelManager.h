#include "raylib.h"
#include "Structs.h"
#include <cstring>
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

    Sound speaking1 = LoadSound("../src/sounds/voice1.mp3");
    Sound speaking2 = LoadSound("../src/sounds/voice2.mp3");

    const char* text1 = "You need to get to the faculty, but public transport has changed its route again. \n \n You came out in WEITI's backyard. Get to the faculty.";
    const char* text2 = "Use the space bar to jump over computers. \n\n The servers are too high, so use W and S to change the path.";

    int textLength1 = strlen(text1);
    int currentLength1 = 0;
    int framesCounter1 = 0;

    int textLength2 = strlen(text2);
    int currentLength2 = 0;
    int framesCounter2 = 0;

    float letterDelay = 1;


    bool DialogueWindow1 = true;
    bool DialogueWindow2 = false;
    bool isRightHalf = true;


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
