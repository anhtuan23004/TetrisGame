#ifndef GAME_H
#define GAME_H

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 480
#define SCALE 20

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <time.h>
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
<<<<<<< HEAD
    void run();
    
    static SDL_Renderer* gameRenderer;
    static TTF_Font* font;
    static SDL_Texture* loadText(string, SDL_Color);
    static void fatalError(string, bool);
    static const int FRAME_RATE = 1000 / 60;
    int fps = 0;
    
=======
    void run();  

    static SDL_Renderer* gameRenderer; 
    static TTF_Font* font;  
    static SDL_Texture* loadText(string, SDL_Color);      
    static void fatalError(string, bool);    

>>>>>>> afeb2a6 ('init')
protected:

private:

<<<<<<< HEAD
    bool initSystem();
    void cleanSystem();
    bool loadFiles();
    void updateScreen();
    void renderChanges();
    void gameLoop();
    void handleGameEvents();
    void renderScore();
    void gameOver();
    void waitForKB();

    SDL_Window* gameWindow;
    SDL_Surface* gameSurface;
    SDL_Event gameEvents;
    GameState gameState;
=======
    bool initSystem();      
    void cleanSystem();     
    bool loadFiles();       
    void updateScreen();    
    void renderChanges();   
    void gameLoop();        
    void handleGameEvents();        
    void renderScore();     
    void gameOver();        

    SDL_Window* gameWindow; 
    SDL_Surface* gameSurface;       
    SDL_Event gameEvents;   
    GameState gameState;    
>>>>>>> afeb2a6 ('init')
    unsigned long long score;
    unsigned long long Highscore;
};

#endif // GAME_H