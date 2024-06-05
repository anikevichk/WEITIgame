#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "raylib.h"
#include "Cell.h"

class Renderer {
public:
    static void DrawMazeWalls(const std::vector<std::vector<Cell>>& maze, int mazeWidth, int mazeHeight,
                              Texture2D& wallH, Texture2D& wallV);
    static void DrawHotdogsAndCollectedText(const std::vector<Rectangle>& hotdogs,
                                            int collectedHotdogs, Texture2D& hotdog);
};

#endif // RENDERER_H
