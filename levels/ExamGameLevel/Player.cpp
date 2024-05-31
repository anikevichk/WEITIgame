#include "Player.h"

Player::Player(int x, int y, int width, int height, int h):health(h) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int Player::GetHealth() {
    return health;
}

void Player::ReceiveDamage(int Damage) {
    health-= Damage;
}

float Player::getSpeed() const {
    return speed;
}

float Player::getDamageRate() const {
    return damageRate;
}

float Player::getDamageTimer() const {
    return damageTimer;
}

void Player::setDamageTimer(float damageTimer) {
    Player::damageTimer = damageTimer;
}

int Player::getCurrentFrame() const {
    return currentFrame;
}

void Player::setCurrentFrame(int currentFrame) {
    Player::currentFrame = currentFrame;
}

const Texture2D &Player::getPlayerSprite() const {
    return playerSprite;
}

Rectangle Player::getCurrentFrames() const {
    return currentFrames[currentFrame];
}

void Player::setCurrentFrames(const Rectangle *currentFrames) {
    Player::currentFrames = currentFrames;
}

void Player::setRunForwardFrames() {
    currentFrames = runForwardFrames;
}

void Player::setRunBackFrames() {
    currentFrames = runBackFrames;
}
void Player::setRunLeftFrames() {
    currentFrames = runLeftFrames;
}

void Player::setRunRightFrames() {
    currentFrames = runRightFrames;
}

float Player::getFrameRate() const {
    return frameRate;
}

float Player::getFrameTimer() const {
    return frameTimer;
}

void Player::setFrameTimer(float frameTimer) {
    Player::frameTimer = frameTimer;
}

int Player::getFrameSize() const {
    return FrameSize;
}

void Player::setFrameSize(int frameSize) {
    FrameSize = frameSize;
}


