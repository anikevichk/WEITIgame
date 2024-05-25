#include "raylib.h"

#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H

class Enemy : public Rectangle{
    int health;
    int damage;
//    bbccaabc
public:
    Enemy(int x, int y, int width, int height, int h, int d);
    int GetHealth();
    int GetDamage();
    void ReceiveDamage(int Damage);
    void moveToPlayer(int playerX, int playerY);

};

#endif //UNTITLED_ENEMY_H