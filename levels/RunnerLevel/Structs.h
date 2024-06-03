#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H
struct Player:Rectangle{
    Player(float x, float y, int width, int height ){
        this-> x = x;
        this -> y = y;
        this->width = width;
        this->height = height;
    }
    bool Climb = false;
    bool isJumping = false;
    float jumpSpeed = 12.0f;
    int normalAlt = 75;
    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    float gravity = 0.4;

    Texture2D playerSprite = LoadTexture("../src/sprite.png");    //textures

    Rectangle frames[2] = {                              //frames for player animation
            {0,  0, 66, 95},
            {73, 0, 66, 95}
    };
};

struct Obstacle:Rectangle{
    Obstacle(float x, float y, int width, int height ){
        this-> x = x;
        this -> y = y;
        this->width = width;
        this->height = height;
    }


};

#endif //UNTITLED_STRUCTS_H
