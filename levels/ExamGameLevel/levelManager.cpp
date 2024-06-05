#include "levelManager.h"
#include <random>
#include <algorithm>

int getRandom(int a, int b, int gapStart, int gapEnd) {           // method used to generate random coordinates of enemies
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);
    int random = dist(gen);


    if (random >= gapStart) {
        random += (gapEnd - gapStart);
    }
    return random;
}


levelManager::levelManager(Window& window) : window(window) {}

void levelManager::Update(){
    player.setFrameTimer(player.getFrameTimer() + GetFrameTime());
    hotdog.hotDogTimer += GetFrameTime();
    enemySpawnerTimer += GetFrameTime();
    player.setDamageTimer(player.getDamageTimer() + GetFrameTime());
    healthBar.x = player.x - 12;
    healthBar.y = player.y - 30;
    healthBar.width =static_cast<int>( 70.0f * (static_cast<float>(player.GetHealth())/100.0f));

}

void levelManager::CheckButtons() {
    if (IsKeyDown(KEY_W)) {
        player.setFrameSize(3);
        player.setRunForwardFrames();
        if(player.y > 0) {
            player.y -= player.getSpeed();
        }
        direction = { 0, -1 };
        isKeyPressed = true;
    }
    else if (IsKeyDown(KEY_D )) {
        player.setFrameSize(2);
        player.setRunRightFrames();
        if (player.x < screenWidth - 25) {
            player.x += player.getSpeed();
        }
        direction = { 1, 0 };
        isKeyPressed = true;

    }
    else if (IsKeyDown(KEY_S)) {
        player.setFrameSize(3);
        if(player.y < screenHeight-25) {
            player.y += player.getSpeed();
        }
        direction = { 0, 1 };

        player.setRunBackFrames();
        isKeyPressed = true;

    }
    else if (IsKeyDown(KEY_A)) {
        player.setFrameSize(2);
        if(player.x > 0) {
            player.x -= player.getSpeed();
        }
        direction = { -1, 0 };
        player.setRunLeftFrames();

        isKeyPressed = true;

    }
     else isKeyPressed = false;


    if (IsKeyPressed(KEY_SPACE)) {
        PlaySound(ThrowEffect);
        float rotate;
        if( direction.x == 1) rotate = 180.0f;
        if( direction.x == -1) rotate = 0.0f;
        if( direction.y == 1) rotate = 270.0f;
        if( direction.y == -1) rotate = 90.0f;

        Bullet newBullet = { { player.x + player.width / 2 + 12, player.y + player.height / 2+20, 5, 5 }, {direction.x * 5.0f, direction.y * 5.0f }, rotate };
        bullets.push_back(newBullet);
    }

}

void levelManager::CheckEnd() {
    if (player.GetHealth() <= 0){
        window.setScreen(Window::LOSS);
        UnloadSound(ThrowEffect);
        UnloadTexture(player.getPlayerSprite());
        UnloadTexture(hotdog.hotdogTexture);
        UnloadTexture(EnemiesTexture);
        UnloadTexture(BulletsTexture);
        End = true;
    }

    if (counter >= 100){
        window.setScreen(Window::VICTORY);
        UnloadSound(ThrowEffect);
        UnloadTexture(player.getPlayerSprite());
        UnloadTexture(hotdog.hotdogTexture);
        UnloadTexture(EnemiesTexture);
        UnloadTexture(BulletsTexture);
        End = true;
    }

}

void levelManager::UpdateplayerSprite() {
    if (player.getFrameTimer() >= player.getFrameRate()) {
        player.setFrameTimer(0.0f);
        if(isKeyPressed) {
            player.setCurrentFrame(player.getCurrentFrame()+1);
            if (player.getCurrentFrame() >= player.getFrameSize()) {
                player.setCurrentFrame(0);
            }
        } else player.setCurrentFrame(0);
    }
}

void levelManager::UpdateHotdog() {
    if (hotdog.hotDogTimer >= hotdog.hotDogRate){
        hotdog.hotDogTimer = 0.0f;
        hotdog.x = GetRandomValue(0, screenWidth);
        hotdog.y = GetRandomValue(0, screenHeight);
    }
    if(CheckCollisionRecs(hotdog, player)){
        player.ReceiveDamage(-25);
        hotdog.x = -30;
        hotdog.y = -30;
    }
}

void levelManager::UpdateEnemy() {
    if(enemySpawnerTimer >= enemySpawnRate) {
        enemySpawnerTimer = 0.0f;
        for (int i = 0; i < 30; i += 2) {
            enemies.emplace_back(getRandom(-100, screenWidth + 100, 0, screenWidth),
                                         getRandom(-100, screenHeight + 100, 0, screenHeight), 30, 50, 5, 25);
            enemies.emplace_back(GetRandomValue(0, screenWidth),
                                         getRandom(-100, screenHeight + 100, 0, screenHeight), 30, 50, 5, 25);

        }
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& enemy) {
        return enemy.GetHealth() <= 0;}), enemies.end());

    for ( auto &enemy : enemies) {
        if (enemy.x >= 0 && enemy.x <= screenWidth && enemy.y >= 0 && enemy.y <= screenHeight) {
            for (auto &bullet: bullets) {
                if (CheckCollisionRecs(enemy, bullet.rect)) {
                    enemy.ReceiveDamage(bullet.Damage);
                    bullet.hit = true;
                    ++counter;
                }

            }

            if (CheckCollisionRecs(enemy, player) && player.getDamageTimer() >= player.getDamageRate()) {
                player.setDamageTimer(0.0f);
                player.ReceiveDamage(enemy.GetDamage());
            }
        }

        enemy.moveToPlayer(player.x + player.width / 2, player.y + player.height / 2);
    }
}

void levelManager::UpdateBullets() {
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) {
        return b.rect.y < 0 ||
               b.rect.y > 900 ||
               b.rect.x < 0 ||
               b.rect.x > 1600 ||
               b.hit; }), bullets.end());



    for (auto &bullet : bullets) {
        bullet.rect.x += bullet.speed.x;
        bullet.rect.y += bullet.speed.y;
    }
}

const Texture2D &levelManager::getBulletsTexture() const {
    return BulletsTexture;
}

const Texture2D &levelManager::getEnemiesTexture() const {
    return EnemiesTexture;
}

int levelManager::getCounter() const {
    return counter;
}

int levelManager::getScreenWidth() const {
    return screenWidth;
}

const Hotdog &levelManager::getHotdog() const {
    return hotdog;
}

const HealthBar &levelManager::getHealthBar() const {
    return healthBar;
}

const Player &levelManager::getPlayer() const {
    return player;
}

int levelManager::getScreenHeight() const {
    return screenHeight;
}
