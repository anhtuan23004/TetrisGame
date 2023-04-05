#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H

#include "Game.h"


class GameBackground 
{
public:
    GameBackground();
    virtual ~GameBackground();

    bool loadBackground(std::string);  
    void drawBackground(); 
    void scrollBackground();  // Cuộn bk

    static const int scrollSpeed = 1;


protected:

private:
    SDL_Texture* backgroundTexture; 
    SDL_Rect backgroundClip; 
};

#endif // GAMEBACKGROUND_H