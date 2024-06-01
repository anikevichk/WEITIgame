#include "raylib.h"
#include "../../Scenes/scenes.h"
#include "enemy.h"
#include "Player.h"
#include "levelManager.h"
#include "../../Tools/DrawTools.h"



bool DialogueWindow = true;
void ExamGame(Window &window) {
    levelManager manager(window);
    Texture2D BackgroundTexture = LoadTexture("../src/levelExam/Background.png");
    Sound ExamSound = LoadSound("../src/sounds/Exam.mp3");

    SetTargetFPS(60);
    PlaySound(ExamSound);
//    while(DialogueWindow && !WindowShouldClose()){
//        BeginDrawing();
//        DrawTexture(BackgroundTexture, 0, 0, WHITE);
//        const char* text = "Test kskksksksk kkskksk ksksk"
//                           " \nTestm jdjdjdjdjjdjj jsjsjj"
//                           "\nskkskkskskskskskkkkkks";
//        DrawRoundedRectangle(600,450, 900, 400, 20,text,DialogueWindow, WHITE);
//        EndDrawing();
//    }

    while (!WindowShouldClose()) {

        if (!IsSoundPlaying(ExamSound))
        {
            PlaySound(ExamSound);
        }
        manager.Update();
        manager.CheckButtons();
        manager.UpdateplayerSprite();
        manager.CheckEnd();
        if(manager.End){
            StopSound(ExamSound);
            UnloadSound(ExamSound);
            UnloadTexture(BackgroundTexture);
            break;
        }
        manager.UpdateHotdog();
        manager.UpdateEnemy();
        manager.UpdateBullets();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(BackgroundTexture, 0, 0, WHITE);

        for (const auto &bullet : manager.bullets) {
            DrawTexturePro(manager.getBulletsTexture(),bullet.Textures[bullet.texture],{bullet.rect.x, bullet.rect.y, 20,6},Vector2 {0,0}, bullet.rotate, WHITE);
        }


        for ( auto &enemy : manager.enemies) {
            DrawTextureRec(manager.getEnemiesTexture(), enemy.getEnemyTextures(),(Vector2) {enemy.x, enemy.y }, WHITE);

        }

        DrawText(TextFormat("100/ %i", manager.getCounter()), manager.getScreenWidth() - 125, 0, 30, BLACK);
        DrawTextureRec(manager.getPlayer().getPlayerSprite(), manager.getPlayer().getCurrentFrames(), (Vector2) {manager.getPlayer().x - 15, manager.getPlayer().y }, WHITE);
        DrawTexture(manager.getHotdog().hotdogTexture, manager.getHotdog().x, manager.getHotdog().y, WHITE );
        DrawRectangleRec(manager.getHealthBar(), RED);


        EndDrawing();
    }

}
