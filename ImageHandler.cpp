#include "imageHandler.h"
#include <SDL_image.h>

<<<<<<< HEAD
imageHandler::imageHandler() {}

imageHandler::~imageHandler() {}
=======
imageHandler::imageHandler(){}

imageHandler::~imageHandler(){}
>>>>>>> afeb2a6 ('init')


SDL_Texture* imageHandler::tiles = nullptr;
SDL_Texture* imageHandler::bk = nullptr;
SDL_Texture* imageHandler::text = nullptr;
SDL_Texture* imageHandler::transparent = nullptr;
SDL_Texture* imageHandler::gameOver = nullptr;
<<<<<<< HEAD
SDL_Texture* imageHandler::titleScreen = nullptr;
=======
SDL_Texture* imageHandler::titleScreen= nullptr;
>>>>>>> afeb2a6 ('init')

SDL_Texture* imageHandler::loadTexture(string path, int r, int g, int b)
{
    SDL_Surface* tempImgSurface = IMG_Load(path.c_str());
<<<<<<< HEAD
    SDL_Texture* retTexture = nullptr;
=======
    SDL_Texture* retTexture = nullptr;   
>>>>>>> afeb2a6 ('init')
    if (tempImgSurface == nullptr)
    {
        Game::fatalError("Images at " + path + " not found", true);
    }
    else
    {
<<<<<<< HEAD
        SDL_SetColorKey(tempImgSurface, SDL_TRUE, SDL_MapRGB(tempImgSurface->format, r, g, b));
        retTexture = SDL_CreateTextureFromSurface(Game::gameRenderer, tempImgSurface);
        SDL_FreeSurface(tempImgSurface);   tempImgSurface = nullptr;
=======
        SDL_SetColorKey(tempImgSurface, SDL_TRUE, SDL_MapRGB(tempImgSurface->format, r, g, b));  
        retTexture = SDL_CreateTextureFromSurface(Game::gameRenderer, tempImgSurface); 
        SDL_FreeSurface(tempImgSurface);   tempImgSurface = nullptr;  
>>>>>>> afeb2a6 ('init')
    }
    return retTexture;
}

bool imageHandler::loadAllImages()
{
    tiles = loadTexture("assets/images/tiles.png", 255, 255, 255);
    bk = loadTexture("assets/images/gameBackground.png", 255, 255, 255);
    transparent = loadTexture("assets/images/transparent.png", 255, 255, 255);
    gameOver = loadTexture("assets/images/gameOver.png", 0, 0, 0);
    titleScreen = loadTexture("assets/images/tetris.png", 0, 0, 255);
<<<<<<< HEAD
    
=======
>>>>>>> afeb2a6 ('init')

    SDL_SetTextureBlendMode(transparent, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(transparent, 130);

    if (!tiles || !bk || !transparent || !gameOver || !titleScreen)
        return false;
    return true;
}

void imageHandler::showImage(SDL_Texture* resourceTexture, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_RenderCopy(Game::gameRenderer, resourceTexture, src, dst);
}

void imageHandler::freeAllMemory()
{
    SDL_DestroyTexture(text);   text = nullptr;
    SDL_DestroyTexture(tiles);   tiles = nullptr;
    SDL_DestroyTexture(bk);   bk = nullptr;
    SDL_DestroyTexture(gameOver);   gameOver = nullptr;
    SDL_DestroyTexture(titleScreen);   titleScreen = nullptr;
}