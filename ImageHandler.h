#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "Game.h"


class imageHandler
{
public:
    imageHandler();
    virtual ~imageHandler();

<<<<<<< HEAD

    static SDL_Texture* tiles;
    static SDL_Texture* bk;
    static SDL_Texture* text;
    static SDL_Texture* transparent;
    static SDL_Texture* gameOver;
    static SDL_Texture* newGame;
    static SDL_Texture* titleScreen;

    static bool loadAllImages();
    static void freeAllMemory();
    static SDL_Texture* loadTexture(string, int, int, int);
=======
    static SDL_Texture* tiles;
    static SDL_Texture* bk;
    static SDL_Texture* text;
    static SDL_Texture* transparent;
    static SDL_Texture* gameOver;
    static SDL_Texture* titleScreen;

    static bool loadAllImages();    
    static void freeAllMemory();    
    static SDL_Texture* loadTexture(string, int, int, int);    
>>>>>>> afeb2a6 ('init')
    static void showImage(SDL_Texture*, SDL_Rect*, SDL_Rect*);

protected:

private:

};

#endif // IMAGEHANDLER_H