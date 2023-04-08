#ifndef GAME_H
#define GAME_H

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 480
#define SCALE 20

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_ttf.h>



using namespace std;

enum GameState { PLAY, EXIT };


class Game
{
public:

    Game();
    virtual ~Game();
    void run(); 

    static SDL_Renderer* gameRenderer; 
    static TTF_Font* font;  
    static SDL_Texture* loadText(string, SDL_Color);   // Chữ màu   
    static void fatalError(string, bool);    
    static const int FPS=60;


protected:

private:

    bool initSystem();      
    void cleanSystem();     
    bool loadFiles();     
    void updateScreen();    
    void renderChanges();   
    void gameLoop();        
    void handleGameEvents();       
    void renderScore();     
    void gameOver();    
    void waitForKBHit(); 

    SDL_Window* gameWindow;
    SDL_Surface* gameSurface;    
    SDL_Event gameEvents;   
    GameState gameState;    
    unsigned long long score;
};

#endif // GAME_H
