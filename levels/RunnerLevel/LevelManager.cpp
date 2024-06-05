#include "LevelManager.h"
#include <cmath>
#include <random>

int lastrandom = 0;
int getRandom() {           // method used to generate random coordinates of obstacles
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(500, 2000);


    int random;
    random = dist(gen);
    if(abs(random - lastrandom)<200){
        random += 200;
    }

    lastrandom = random;
    return random;
}


bool LevelManager::isLoss() const {
    return loss;
}

void LevelManager::setLoss(bool loss) {
    LevelManager::loss = loss;
}

void LevelManager::InitLevel() {
    for (auto &obstacle: obstacles) {   //random generation of start postion of obstacles
        int random = getRandom();

        obstacle.x = obstacle.x + random;
    }

    player.y = screenHeight - player.normalAlt;        //set y coordinate of player

}

void LevelManager::CheckObstacle() {
    for (auto &obstacle: obstacles) {   //check all obstacles
        obstacle.x -= obstacleSpeed;


        if (CheckCollisionRecs(player, obstacle)) {     //check collisions betwet player and all obstacles

            obstacleSpeed = 0.0f;

            UnloadSound(JumpEffect);
            UnloadTexture(player.playerSprite);
            UnloadTexture(obstacleTexture);
            UnloadTexture(serverTexture);

            UnloadTexture(floorTexture);

            loss = true;
        }


        if (obstacle.x < 0) {                       // when obstacle reach end of the map, set new x coordinate
            int random = getRandom();
            obstacle.x = screenWidth + random;
            counter++;
        }

    }
}

bool LevelManager::isVictory() {
    if (counter >= 50) {                            //check if reguired amount of point was reached
        obstacleSpeed = 0.0f;
        UnloadSound(JumpEffect);
        UnloadTexture(player.playerSprite);
        UnloadTexture(obstacleTexture);
        UnloadTexture(serverTexture);
        UnloadTexture(floorTexture);
        return true;
    }
    return false;
}

void LevelManager::CheckJump() {
    if (IsKeyDown(KEY_SPACE) && !player.isJumping) {   //check space key, that used for jumping
        player.isJumping = true;
        PlaySound(JumpEffect);
    }


    if (player.y != screenHeight - player.normalAlt && player.Climb) {    //jump animation when player chang floor
        player.y = screenHeight - player.normalAlt;
        player.isJumping = true;
    }


    if (player.isJumping) {            //jump
        player.y -= player.jumpSpeed;
        player.jumpSpeed -= player.gravity;
        if (player.y > screenHeight - player.normalAlt) {
            player.y = screenHeight - player.normalAlt;
            player.isJumping = false;
            player.jumpSpeed = 10.0f;
        }
    }
}

void LevelManager::CheckClimb() {
    if (IsKeyReleased(KEY_W)) {     // check if W key realeasd, that used to go upper floor
        player.Climb = false;
    }

    if (IsKeyDown(KEY_W) && !player.Climb) {   // check if W key pressed, change y, coordinate of player
        PlaySound(JumpEffect);
        player.Climb = true;


        if (player.normalAlt >= 350 && player.normalAlt < 625) {
            player.normalAlt = 625;
        }

        if (player.normalAlt < 350) {
            player.normalAlt = 350;
        }
    }

    if (IsKeyReleased(KEY_S)) {    // check if W key realeasd, that used to go lower floor
        PlaySound(JumpEffect);
        player.Climb = false;
    }

    if (IsKeyDown(KEY_S) && !player.Climb) {   // check if S key pressed, change y, coordinate of player

        player.Climb = true;

        if (player.normalAlt <= 350) {
            player.normalAlt = 75;
        }

        if (player.normalAlt > 350) {
            player.normalAlt = 350;
        }

    }
}

void LevelManager::UpdateFrame() {
    player.frameTimer += GetFrameTime();   //frame changer
    if (player.frameTimer >= player.frameRate) {
        player.frameTimer = 0.0f;
        player.currentFrame++;

        if (player.currentFrame >= sizeof(player.frames) / sizeof(Rectangle)) {
            player.currentFrame = 0;
        }
    }
}

int LevelManager::getCounter() const {
    return counter;
}

const Texture2D &LevelManager::getFloorTexture() const {
    return floorTexture;
}

const Rectangle &LevelManager::getFloor1() const {
    return floor1;
}

const Rectangle &LevelManager::getFloor2() const {
    return floor2;
}

const Rectangle &LevelManager::getFloor3() const {
    return floor3;
}

const Texture2D &LevelManager::getObstacleTexture() const {
    return obstacleTexture;
}

const Texture2D &LevelManager::getServerTexture() const {
    return serverTexture;
}

 Player &LevelManager::getPlayer()  {
    return player;
}

 Obstacle &LevelManager::getObstacles(int index)  {
    return obstacles[index];
}

int LevelManager::getScreenWidth() const {
    return screenWidth;
}

void LevelManager::setCounter(int counter) {
    LevelManager::counter = counter;
}

const Obstacle *LevelManager::getObstacles1() const {
    return obstacles;
}
