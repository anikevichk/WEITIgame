#include"raylib.h"

#ifndef UNTITLED_TOOLS_H
#define UNTITLED_TOOLS_H

class Window{
public:
    typedef enum GameScreen { Menu, LEVEL1, LOSS, VICTORY, EXAM, MAZE, CATCH, MAIN } GameScreen;
private:
    GameScreen currentScreen;
public:
    void setScreen(GameScreen newScreen);
     GameScreen getScreen(){
         return currentScreen;
     }
};

#endif //UNTITLED_TOOLS_H
