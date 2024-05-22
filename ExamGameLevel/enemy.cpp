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