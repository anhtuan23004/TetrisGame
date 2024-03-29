﻿#ifndef GAME_H
#define GAME_H

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 480
#define SCALE 20
#define rNewBlock 23
#define cNewBlock 18
#define NewBlockRow 0
#define NewBlockCol 4

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
    void run();
    
    static SDL_Renderer* gameRenderer;
    static TTF_Font* font;
    static SDL_Texture* loadText(string, SDL_Color);
    static void fatalError(string, bool);
    static const int FRAME_RATE = 1000 / 60;
    int fps = 0;

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
    void waitForStart();

    SDL_Surface* icon;
    SDL_Window* gameWindow;
    SDL_Surface* gameSurface;
    SDL_Event gameEvents;
    GameState gameState;
    unsigned long long score;
    unsigned long long Highscore;
};

#endif // GAME_H