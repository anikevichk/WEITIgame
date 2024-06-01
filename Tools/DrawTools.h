#include "raylib.h"

#ifndef UNTITLED_DRAWTOOLS_H
#define UNTITLED_DRAWTOOLS_H

void DrawRoundedRectangle(int posX, int posY, int width, int height, float radius, const char* text, bool& flag, Color color, const char* name = "Next");
void drawTeachers(bool isInRightHalf);
void DrawDialogueWindow(const char* text, int& currentLength, int textLength, int& framesCounter, Sound speaking,
                        Texture2D& background, float letterDelay, bool& isDialogueWindowOpen, bool& isRightHalf);
void HandleDialogueWindow(const char* text, int& currentLength, int textLength, int& framesCounter, Sound speaking,
                          Texture2D& background, float letterDelay, bool& isDialogueWindowOpen, bool& isRightHalf);
void unloadTeachers();

#endif //UNTITLED_DRAWTOOLS_H
