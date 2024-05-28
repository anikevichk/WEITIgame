#include "raylib.h"
#include "../../Scenes/scenes.h"
#include "maze.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <ctime>
#include <set>

void Maze(Window &window) {
    int screenWidth = 1600;
    int screenHeight = 900;
    float speed = 5.0f;
    SetTargetFPS(60);

    int currentFrame = 0;
    float frameRate = 0.1f;
    float frameTimer = 0.0f;
    bool isKeyPressed = false;

    float scale = 0.8f;

    Rectangle runRightFrames[] = {
            {0,   0, 66, 95},
            {73,  0, 66, 95},
            {146, 0, 66, 95}
    };
    Rectangle runLeftFrames[] = {
            {0,   104, 66, 95},
            {73,  104, 66, 95},
            {146, 104, 66, 95}
    };
    Rectangle runBackFrames[] = {
            {0,   208, 73, 95},
            {75,  208, 73, 95},
            {158, 208, 73, 95}
    };
    Rectangle runForwardFrames[] = {
            {0,   312, 73, 95},
            {75,  312, 73, 95},
            {158, 312, 73, 95}
    };
    Rectangle *currentFrames = runRightFrames;

    int mazeWidth = screenWidth / CELL_SIZE;
    int mazeHeight = screenHeight / CELL_SIZE;

    Rectangle player = {15, 807, 70.0f * scale, 90.0f * scale};

    std::vector<std::vector<Cell>> maze(mazeWidth, std::vector<Cell>(mazeHeight));

    // Генерация лабиринта
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            maze[x][y] = { x, y, false, true, true, true, true };
        }
    }
    std::stack<Cell*> stack;
    srand(time(0));
    int startX = rand() % mazeWidth;
    int startY = rand() % mazeHeight;
    maze[startX][startY].visited = true;
    stack.push(&maze[startX][startY]);
    while (!stack.empty()) {
        Cell* current = stack.top();
        std::vector<Cell*> neighbors;
        if (current->x > 0 && !maze[current->x - 1][current->y].visited) {
            neighbors.push_back(&maze[current->x - 1][current->y]);
        }
        if (current->x < mazeWidth - 1 && !maze[current->x + 1][current->y].visited) {
            neighbors.push_back(&maze[current->x + 1][current->y]);
        }
        if (current->y > 0 && !maze[current->x][current->y - 1].visited) {
            neighbors.push_back(&maze[current->x][current->y - 1]);
        }
        if (current->y < mazeHeight - 1 && !maze[current->x][current->y + 1].visited) {
            neighbors.push_back(&maze[current->x][current->y + 1]);
        }
        if (!neighbors.empty()) {
            Cell* next = neighbors[rand() % neighbors.size()];
            if (next->x == current->x - 1) {
                current->leftWall = false;
                next->rightWall = false;
            } else if (next->x == current->x + 1) {
                current->rightWall = false;
                next->leftWall = false;
            } else if (next->y == current->y - 1) {
                current->topWall = false;
                next->bottomWall = false;
            } else if (next->y == current->y + 1) {
                current->bottomWall = false;
                next->topWall = false;
            }
            next->visited = true;
            stack.push(next);
        } else {
            stack.pop();
        }
    }

    Texture2D hotdog = LoadTexture("../src/hotdog.png");
    Texture2D wallH = LoadTexture("../src/levelMaze/wallH.png");
    Texture2D wallV = LoadTexture("../src/levelMaze/wallV.png");
    Texture2D sprite = LoadTexture("../src/sprite.png");
    Texture2D background = LoadTexture("../src/levelMaze/background.png");

    Sound mainTheme = LoadSound("../src/sounds/MazeMainTheme.mp3");
    Sound bonus = LoadSound("../src/sounds/bonus.wav");
    SetSoundVolume(bonus, 0.3);

    std::vector<Rectangle> hotdogs;
    srand(time(0));
    std::set<std::pair<int, int>> occupiedCells;
    while (hotdogs.size() < 5) {
        int hotdogX = rand() % mazeWidth;
        int hotdogY = rand() % mazeHeight;
        if (occupiedCells.find({hotdogX, hotdogY}) == occupiedCells.end()) {
            Rectangle hotdogRect = {static_cast<float>(hotdogX * CELL_SIZE + CELL_SIZE / 4),
                                    static_cast<float>(hotdogY * CELL_SIZE + CELL_SIZE / 4), 75, 75};
            hotdogs.push_back(hotdogRect);
            occupiedCells.insert({hotdogX, hotdogY});
        }
    }

    int collectedHotdogs = 0;
    bool gameWon = false;

    while (!WindowShouldClose()) {
        if (!IsSoundPlaying(mainTheme)) {
            PlaySound(mainTheme);
        }

        Vector2 direction = {0, 0};

        Rectangle previousPosition = player;
        if (IsKeyDown(KEY_W)) {
            direction = {0, -speed};
            currentFrames = runForwardFrames;
            isKeyPressed = true;
        } else if (IsKeyDown(KEY_S)) {
            direction = {0, speed};
            currentFrames = runBackFrames;
            isKeyPressed = true;
        } else if (IsKeyDown(KEY_A)) {
            direction = {-speed, 0};
            currentFrames = runLeftFrames;
            isKeyPressed = true;
        } else if (IsKeyDown(KEY_D)) {
            direction = {speed, 0};
            currentFrames = runRightFrames;
            isKeyPressed = true;
        } else {
            isKeyPressed = false;
        }

        Rectangle newPlayerPos = {player.x + direction.x, player.y + direction.y, player.width, player.height};
        int x1 = static_cast<int>(newPlayerPos.x) / CELL_SIZE;
        int y1 = static_cast<int>(newPlayerPos.y) / CELL_SIZE;
        int x2 = static_cast<int>(newPlayerPos.x + newPlayerPos.width) / CELL_SIZE;
        int y2 = static_cast<int>(newPlayerPos.y + newPlayerPos.height) / CELL_SIZE;

        bool collision = false;
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                if (x >= 0 && x < mazeWidth && y >= 0 && y < mazeHeight) {
                    Cell cell = maze[x][y];
                    if (cell.topWall && newPlayerPos.y <= y * CELL_SIZE) collision = true;
                    if (cell.bottomWall && newPlayerPos.y + newPlayerPos.height >= (y + 1) * CELL_SIZE) collision = true;
                    if (cell.leftWall && newPlayerPos.x <= x * CELL_SIZE) collision = true;
                    if (cell.rightWall && newPlayerPos.x + newPlayerPos.width >= (x + 1) * CELL_SIZE) collision = true;
                }
            }
        }
        if (!collision) {
            player.x += direction.x;
            player.y += direction.y;
        } else {
            player = previousPosition;
        }

        for (auto &hotdogRect: hotdogs) {
            if (CheckCollisionRecs(player, hotdogRect)) {
                PlaySound(bonus);
                hotdogRect = {-CELL_SIZE, -CELL_SIZE, 0, 0};
                collectedHotdogs++;
            }
        }

        if (collectedHotdogs == 5 && player.x > (mazeWidth - 1) * CELL_SIZE && player.y < CELL_SIZE) {
            gameWon = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        frameTimer += GetFrameTime();
        if (frameTimer >= frameRate) {
            frameTimer = 0.0f;
            if (isKeyPressed) {
                currentFrame++;
                if (currentFrame >= 3) {
                    currentFrame = 0;
                }
            } else {
                currentFrame = 0;
            }
        }

        DrawTexture(background, 0, 0, WHITE);

        Rectangle sourceRec = currentFrames[currentFrame];
        Rectangle destRec = {player.x, player.y, sourceRec.width * scale, sourceRec.height * scale};
        Vector2 origin = {sourceRec.width * scale / 600, sourceRec.height * scale / 24 };
        DrawTexturePro(sprite, sourceRec, destRec, origin, 0.0f, WHITE);

        for (int x = 0; x < mazeWidth; x++) {
            for (int y = 0; y < mazeHeight; y++) {
                if (maze[x][y].topWall) {
                    DrawTexture(wallH, x * CELL_SIZE, y * CELL_SIZE, WHITE);
                }
                if (maze[x][y].bottomWall) {
                    DrawTexture(wallH, x * CELL_SIZE, (y + 1) * CELL_SIZE, WHITE);
                }
                if (maze[x][y].leftWall) {
                    DrawTexture(wallV, x * CELL_SIZE, y * CELL_SIZE, WHITE);
                }
                if (maze[x][y].rightWall) {
                    DrawTexture(wallV, (x + 1) * CELL_SIZE, y * CELL_SIZE, WHITE);
                }
            }
        }

        for (const auto &hotdogRect: hotdogs) {
            if (hotdogRect.width > 0 && hotdogRect.height > 0) {
                DrawTexture(hotdog, hotdogRect.x, hotdogRect.y, WHITE);
            }
        }

        DrawText(TextFormat("Collected: %d/5", collectedHotdogs), 10, 10, 20, BLACK);

        if (gameWon) {
            window.setScreen(Window::VICTORY);
            break;
        }

        EndDrawing();
    }

    UnloadTexture(hotdog);
    UnloadTexture(wallH);
    UnloadTexture(wallV);
    UnloadTexture(background);

    StopSound(mainTheme);
    UnloadSound(mainTheme);
    UnloadSound(bonus);
}
