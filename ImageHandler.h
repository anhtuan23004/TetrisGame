#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "Game.h"


class imageHandler
{
public:
    imageHandler();
    virtual ~imageHandler();

    // Trỏ đến nơi chứa ảnh
    static SDL_Texture* tilesTexture;
    static SDL_Texture* bkTexture;
    static SDL_Texture* text;
    static SDL_Texture* transparentTexture;
    static SDL_Texture* gameOverTexture;
    static SDL_Texture* newGameTexture;
    static SDL_Texture* titleScreenTexture;

    static bool loadAllImages();    
    static void freeAllMemory();    
    static SDL_Texture* loadTexture(string, int, int, int);    
    static void showImage(SDL_Texture*, SDL_Rect*, SDL_Rect*);

protected:

private:

};

#endif // IMAGEHANDLER_H
