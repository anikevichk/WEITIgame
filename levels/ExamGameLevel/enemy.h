#include "raylib.h"

#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H

class Enemy : public Rectangle{
    int health;
    int damage;
    int texture;
    Rectangle Textures[4] = {
            {0,0,46, 50},
            {47,0,40, 50},
            {87,0,47, 50},
            {134, 0, 40,50}
    };
public:
    const Rectangle getEnemyTextures() const;
    Enemy(int x, int y, int width, int height, int h, int d);
    int GetHealth();
    int GetDamage();
    int GetTexture();
    void ReceiveDamage(int Damage);
    void moveToPlayer(int playerX, int playerY);

};

#endif //UNTITLED_ENEMY_H
