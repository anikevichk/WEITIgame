
#include "raylib.h"
#include "../../Scenes/scenes.h"
#include "../../Tools/DrawTools.h"
#include "LevelManager.h"


void level1(Window &window) {



    bool DialogueWindow = true;


    LevelManager manager;





    Sound RunnerSound = LoadSound("../src/sounds/Runner.mp3");
    Texture2D backgroundTexture = LoadTexture("../src/levelRunner/background.png");

    manager.InitLevel();

    PlaySound(RunnerSound);
//    while(DialogueWindow && !WindowShouldClose()){
//        BeginDrawing();
//        DrawTexture(backgroundTexture, 0, 0, WHITE);
//        const char* text = "Test kskksksksk kkskksk ksksk"
//                           " \nTestm jdjdjdjdjjdjj jsjsjj"
//                           "\nskkskkskskskskskkkkkks";
//        DrawRoundedRectangle(600,450, 900, 400, 20,text,DialogueWindow, WHITE);
//        EndDrawing();
//    }

    while (!WindowShouldClose()) {

        if (!IsSoundPlaying(RunnerSound))
        {
            PlaySound(RunnerSound);
        }

        manager.CheckObstacle();

        if (manager.isLoss()) {                                     //check if loss flag was setted
            window.setScreen(Window::LOSS);
            StopSound(RunnerSound);
            UnloadSound(RunnerSound);
            UnloadTexture(backgroundTexture);
            break;
        }

        if (manager.isVictory()) {                                     //check if loss flag was setted
            window.setScreen(Window::VICTORY);
            StopSound(RunnerSound);
            UnloadSound(RunnerSound);
            UnloadTexture(backgroundTexture);
            break;
        }





        manager.CheckJump();
        manager.CheckClimb();
        manager.UpdateFrame();






        BeginDrawing();
        //draw all objects
        ClearBackground(RAYWHITE);
        DrawTexture(backgroundTexture, 0, 0, WHITE);
        DrawTexture(manager.getFloorTexture(), manager.getFloor1().x, manager.getFloor1().y, WHITE);
        DrawTexture(manager.getFloorTexture(), manager.getFloor2().x, manager.getFloor2().y, WHITE);
        DrawTexture(manager.getFloorTexture(), manager.getFloor3().x, manager.getFloor3().y, WHITE);
        DrawTextureRec(manager.getPlayer().playerSprite, manager.getPlayer().frames[manager.getPlayer().currentFrame], (Vector2) {manager.getPlayer().x - 45, manager.getPlayer().y - 50}, WHITE);
        DrawTexture(manager.getObstacleTexture(), manager.getObstacles(0).x - 45, manager.getObstacles(0).y - 50, WHITE);
        DrawTexture(manager.getObstacleTexture(), manager.getObstacles(1).x - 45, manager.getObstacles(1).y - 50, WHITE);
        DrawTexture(manager.getObstacleTexture(), manager.getObstacles(2).x - 45, manager.getObstacles(2).y - 50, WHITE);
        DrawTexture(manager.getServerTexture(), manager.getObstacles(3).x - 45, manager.getObstacles(3).y - 50, WHITE);
        DrawTexture(manager.getServerTexture(), manager.getObstacles(4).x - 45, manager.getObstacles(4).y - 50, WHITE);
        DrawTexture(manager.getServerTexture(), manager.getObstacles(5).x - 45, manager.getObstacles(5).y - 50, WHITE);

        DrawText(TextFormat("50/ %i", manager.getCounter()), manager.getScreenWidth() - 125, 0, 30, WHITE);

        EndDrawing();
    }


}

