#include "enemy.h"
#include "raylib.h"

Enemy::Enemy(int x, int y, int width, int height, int h, int d) : health(h), damage(d){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;}

int Enemy::GetHealth() {
    return health;
}

int Enemy::GetDamage() {
    return damage;
}

void Enemy::ReceiveDamage(int Damage) {
    health -= Damage;
}

void Enemy::moveToPlayer(int playerX, int playerY){
    int distanceX = playerX - x;
    int distanceY = playerY - y;
    int sideX = 1;
    int sideY = 1;

    if (distanceX < 0) sideX = -1;
    if (distanceY < 0) sideY = -1;

   if(playerX != x) x+=sideX;
    if(playerY != y) y+=sideY;

}