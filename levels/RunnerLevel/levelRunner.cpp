
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


    SetSoundVolume(RunnerSound, 0.3);

    HandleDialogueWindow(manager.text1, manager.currentLength1, manager.textLength1, manager.framesCounter1, manager.speaking1,
                         backgroundTexture, manager.letterDelay, manager.DialogueWindow1, manager.isRightHalf);
    if (!manager.DialogueWindow1) {
        manager.DialogueWindow2 = true;
        manager.isRightHalf = false;
    }

    HandleDialogueWindow(manager.text2, manager.currentLength2, manager.textLength2, manager.framesCounter2, manager.speaking2,
                         backgroundTexture, manager.letterDelay, manager.DialogueWindow2, manager.isRightHalf);
    SetSoundVolume(RunnerSound, 0.7);

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

