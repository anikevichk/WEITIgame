#include "raylib.h"

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H
class Player : public Rectangle{
    int health;
    int texture;
    int currentFrame = 0;
    int FrameSize;
    float speed = 2.0f;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    float damageRate = 2.0f;
    float damageTimer = 2.0f;
    const Rectangle* currentFrames = runRightFrames;
    Texture2D playerSprite = LoadTexture("../src/sprite.png");
    Rectangle runForwardFrames[3] = {                              //frames for player animation
            {0,  312, 73, 95},
            {80,  312, 73, 95},
            {160,  312, 73, 95}
    };
    Rectangle runBackFrames[3] = {                              //frames for player animation
            {0,  208, 73, 95},
            {80,  208, 73, 95},
            {160,  208, 73, 95}

    };
    Rectangle runLeftFrames[3] = {                              //frames for player animation
            {0,  104, 70, 95},
            {73, 104, 70, 95},
            {146, 104, 70, 95}
    };

    Rectangle runRightFrames[3] = {                              //frames for player animation
            {0,  0, 70, 95},
            {73, 0, 70, 95},
            {146, 0, 70, 95}
    };
public:
     Rectangle getCurrentFrames() const;
    void setCurrentFrames(const Rectangle *currentFrames);
    void setRunForwardFrames();
    void setRunBackFrames();
    void setRunLeftFrames();
    void setRunRightFrames();
    const Texture2D &getPlayerSprite() const;
    int getCurrentFrame() const;
    void setCurrentFrame(int currentFrame);
    void setDamageTimer(float damageTimer);
    void setFrameTimer(float frameTimer);
    float getFrameTimer() const;
    float getFrameRate() const;
    float getDamageTimer() const;
    float getDamageRate() const;
    float getSpeed() const;
    int getFrameSize() const;
    void setFrameSize(int frameSize);
public:
    Player(int x, int y, int width, int height, int h);
    int GetHealth();
    void ReceiveDamage(int Damage);
};


#endif //UNTITLED_PLAYER_H
