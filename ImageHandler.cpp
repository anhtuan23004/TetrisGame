#include "imageHandler.h"
#include <SDL_image.h>

imageHandler::imageHandler(){}

imageHandler::~imageHandler(){}


SDL_Texture* imageHandler::tilesTexture = nullptr;
SDL_Texture* imageHandler::bkTexture = nullptr;
SDL_Texture* imageHandler::text = nullptr;
SDL_Texture* imageHandler::transparentTexture = nullptr;
SDL_Texture* imageHandler::gameOverTexture = nullptr;
SDL_Texture* imageHandler::newGameTexture = nullptr;
SDL_Texture* imageHandler::titleScreenTexture = nullptr;

// Tải ảnh có kết cấu
SDL_Texture* imageHandler::loadTexture(string path, int r, int g, int b)
{
    SDL_Surface* tempImgSurface = IMG_Load(path.c_str()); // tạo ảnh trên màn hình
    SDL_Texture* retTexture = nullptr;    // Trả lại kết cấu
    if (tempImgSurface == nullptr) // Nếu ảnh không chạy được
    {
        Game::fatalError("Images at " + path + " not found", true);
    }
    else
    {
        SDL_SetColorKey(tempImgSurface, SDL_TRUE, SDL_MapRGB(tempImgSurface->format, r, g, b));  
        retTexture = SDL_CreateTextureFromSurface(Game::gameRenderer, tempImgSurface); 
        SDL_FreeSurface(tempImgSurface);   tempImgSurface = nullptr;  // Giải phóng thứ kh cần thiết trên màn hình
    }
    return retTexture;  // Cả ảnh và kết cấu
}

bool imageHandler::loadAllImages()
{
    // Tải file ảnh
    tilesTexture = loadTexture("assets/images/Tiles.png", 255, 255, 255);
    bkTexture = loadTexture("assets/images/gameBackground.png", 255, 255, 255);
    transparentTexture = loadTexture("assets/images/transparent.png", 255, 255, 255);
    gameOverTexture = loadTexture("assets/images/gameOver.png", 0, 0, 0);
    newGameTexture = loadTexture("assets/images/newGame.png", 0, 0, 255);
    titleScreenTexture = loadTexture("assets/images/title.png", 0, 0, 255);

    // Làm trong suốt
    SDL_SetTextureBlendMode(transparentTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(transparentTexture, 130);

    // Kiểm tra xem chạy được hay không
    if (!tilesTexture || !bkTexture || !transparentTexture || !gameOverTexture || !newGameTexture || !titleScreenTexture)
        return false;
    return true;
}

void imageHandler::showImage(SDL_Texture* resourceTexture, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_RenderCopy(Game::gameRenderer, resourceTexture, src, dst); // Sao chép ảnh ở vị trí đặc biệt
}

void imageHandler::freeAllMemory()
{
    // Giải phóng bộ nhớ động
    SDL_DestroyTexture(text);   text = nullptr;
    SDL_DestroyTexture(tilesTexture);   tilesTexture = nullptr;
    SDL_DestroyTexture(bkTexture);   bkTexture = nullptr;
    SDL_DestroyTexture(gameOverTexture);   gameOverTexture = nullptr;
    SDL_DestroyTexture(newGameTexture);   newGameTexture = nullptr;
    SDL_DestroyTexture(titleScreenTexture);   titleScreenTexture = nullptr;
}
