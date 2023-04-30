
#include "GameCanvas.h"
#include "Block.h"
#include "soundHandler.h"
#include <SDL_image.h>

Block currentBlock;
Block nextBlock;

GameCanvas canvas;

Game::Game()
{
    gameSurface = nullptr;   gameWindow = nullptr;  icon = nullptr;

    gameState = PLAY;

    score = 0;

    Highscore = 0;

    srand(time(nullptr));
}

Game::~Game()
{
    gameSurface = nullptr;    gameRenderer = nullptr;  icon = nullptr;
    gameWindow = nullptr;   font = nullptr;
}

SDL_Renderer* Game::gameRenderer = nullptr;
TTF_Font* Game::font = nullptr;

void Game::fatalError(string error, bool closeProgram)
{
    cout << "Error Occured : " << error << endl;
    if (closeProgram)
    {
        Game out;
        out.cleanSystem();
        cin.get();
        exit(-1);
    }
}

SDL_Texture* Game::loadText(string text, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(Game::font, text.c_str(), color);
    SDL_Texture* ret = SDL_CreateTextureFromSurface(gameRenderer, textSurface);
    SDL_FreeSurface(textSurface);   textSurface = nullptr;
    return ret;
}


void Game::run()
{
    if (!initSystem())
    {
        cout << "Error in INITIALIZING System " << endl; cin.get(); return;
    }
    if (!loadFiles())
    {
        cout << "Error in Loading Files " << endl;  cin.get();  return;
    }

    SDL_SetWindowIcon(gameWindow, icon);

    imageHandler::showImage(imageHandler::titleScreen, nullptr, nullptr);
    renderChanges();

    stringstream StartGame;
    StartGame << "Press space bar or click mouse once to begin!";
    SDL_Color textColor = { 0, 0, 0,255 };
    imageHandler::text = loadText(StartGame.str().c_str(), textColor);
    SDL_Rect startGame = { 60,520,400 - 40,480 - 440 };
    imageHandler::showImage(imageHandler::text, nullptr, &startGame);

    renderChanges();

    gameState = PLAY;

    waitForKB();

    while (gameState == PLAY)
    {
        gameLoop();
    }

    cleanSystem();
}


bool Game::initSystem()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    gameWindow = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gameSurface = SDL_GetWindowSurface(gameWindow);
    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);

    icon = IMG_Load("assets/images/gg.jpg");

    return true;
}

void Game::cleanSystem()
{
    SDL_FreeSurface(gameSurface);
    SDL_DestroyRenderer(gameRenderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(gameWindow);
    imageHandler::freeAllMemory();
    soundHandler::freeAllSounds();

    Mix_Quit();  TTF_Quit();  IMG_Quit();  SDL_Quit();
}

bool Game::loadFiles()
{
    font = TTF_OpenFont("assets/fonts/font.ttf", 32);
    if (!font || !imageHandler::loadAllImages() || !soundHandler::loadAllSounds())
        return false;
    return true;
}

void Game::handleGameEvents()
{
    while (SDL_PollEvent(&gameEvents))
    {
        switch (gameEvents.type)
        {
        case SDL_QUIT:
            gameState = EXIT;
            break;
        case SDL_KEYDOWN:
            if (gameEvents.key.keysym.sym == SDLK_UP)
            {
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                currentBlock.rotateBlock();
            }
            else if (gameEvents.key.keysym.sym == SDLK_DOWN)
            {
                // if u want block to fall down in steps

                // clear block from canvas
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                // if there is no collision happening
                if (!canvas.checkForStopCondition(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
                {
                    soundHandler::playMovementEffect();
                    int newRow = currentBlock.getRowNo();
                    newRow++;
                    currentBlock.setRowNo(newRow);
                }
            }
            else if (gameEvents.key.keysym.sym == SDLK_LEFT)  // a to move block left
            {
                // clear block from canvas
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                // only move block to left if there is chance of moving
                if (canvas.isLeftMovePossible(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
                    currentBlock.moveBlockHoriz(0); // 0 passed as argument to indicate left movement
            }
            else if (gameEvents.key.keysym.sym == SDLK_RIGHT)
            {
                // clear block from canvas
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                // only move block to right if there is chance of moving

                if (canvas.isRightMovePossible(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
                    currentBlock.moveBlockHoriz(1); // 1 indicates right movement of block
            }
            break;
        }
    }
}
void Game::updateScreen()
{
    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gameRenderer);

    string title = "Tetris Game -- FPS : " + to_string(fps);
    SDL_SetWindowTitle(gameWindow, title.c_str());
    // render the background image
    imageHandler::showImage(imageHandler::bk, nullptr, nullptr);

    // clear both, current and next block from canvas
    canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
    canvas.clearBlockFromCanvas(nextBlock.blockPattern, nextBlock.getRowNo(), nextBlock.getColNo());

    // move our current block down as its default motion
    currentBlock.moveBlockDown();

    // copy our block pattern on canvas
    canvas.copyBlockToCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
    // check for collision
    if (canvas.checkForStopCondition(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
    {
        score += 5;   // give +5 score if the block is placed
        if (canvas.unifyColor()) // check for the game over condition
        {           
            canvas.showMatrix();
            SDL_Delay(1234);
            gameState = EXIT;     // make the game ends here
            return;    
        }
        while (canvas.destroyRows())    // check if there is availability of destroying rows
        {
            soundHandler::playDestructionEffect();  // play sound effect for row destruction
            score += 20;      // +20 score if a row destroys
        }
        currentBlock = nextBlock; // make the next block as current block
        currentBlock.setRowNo(0);  currentBlock.setColNo(4);    // reset position of current block
        nextBlock.createNewBlock(23, 18);    // create a new next block
    }

    // copy our next block pattern to canvas
    canvas.copyBlockToCanvas(nextBlock.blockPattern, nextBlock.getRowNo(), nextBlock.getColNo());

    // show our canvas
    canvas.showMatrix();

    renderScore();

}

void Game::renderChanges()
{
    SDL_RenderPresent(gameRenderer);    // apply all changes on screen
}

// main game loop
void Game::gameLoop()
{
    soundHandler::playBGM();    // start BGM
    score = 0;        // init score to 0
    Highscore = 0;

    Uint32 before, second = SDL_GetTicks(), after;
    int frame_time, frames = 0;

    // create two blocks of game
    currentBlock.createNewBlock(0, 4);
    nextBlock.createNewBlock(23, 18);
    while (gameState == PLAY)
    {
        before = SDL_GetTicks();
 
        handleGameEvents(); // handle all game events
        updateScreen();     // make changes accordingly on screen
        renderChanges();    // render all changes on screen

        frames++;
        after = SDL_GetTicks();
        frame_time = after - before;

        if (after - second >= 1000)
        {
            fps = frames;
            frames = 0;
            second = after;
            updateScreen();


        }
        if (FRAME_RATE > frame_time)
        {
            SDL_Delay(FRAME_RATE - frame_time);
        }
    }
    soundHandler::stopBGM();    // stop BGM
    gameOver(); // handle the game over scene
}

// handles score board on game screen
void Game::renderScore()
{
    stringstream scoreStr;  // stringsteam used for score
    scoreStr << " " << score << " ";
    stringstream HighscoreStr;
    HighscoreStr << " " << Highscore << " ";
    SDL_Color textColor = { 127,0,255,255 };

    std::ifstream readfile("HighScore.txt");
    if (readfile)
    {
        unsigned int max;
        readfile >> max;
        Highscore = max;
        readfile.close();
    }

    if (score > Highscore) Highscore = score;
    if (imageHandler::text)
    {
        SDL_DestroyTexture(imageHandler::text);   imageHandler::text = nullptr;
    }
    // render score on screen
    imageHandler::text = loadText(scoreStr.str().c_str(), textColor);
    SDL_Rect scoreBoard = { 340,110,440 - 340,150 - 110 };
    imageHandler::showImage(imageHandler::text, nullptr, &scoreBoard);

    imageHandler::text = loadText(HighscoreStr.str().c_str(), textColor);
    SDL_Rect HighscoreBoard = { 340, 240,440 - 340,150 - 110 };
    imageHandler::showImage(imageHandler::text, nullptr, &HighscoreBoard);
}

void Game::gameOver()
{
    soundHandler::playGameOverEffect(); // play game over sound effect
    imageHandler::showImage(imageHandler::transparent, nullptr, nullptr);  // make background transparent

    // show game over image
    SDL_Rect gameOverRect = { 40,40,440 - 40,380 - 120 };
    imageHandler::showImage(imageHandler::gameOver, nullptr, &gameOverRect);

    // render final score on screen
    stringstream scoreStr;
    stringstream HighscoreStr;
    if (score > Highscore) Highscore = score;
    scoreStr << " SCORE : " << score << " ";
    HighscoreStr << "HIGH-SCORE : " << Highscore << " ";
    SDL_Color textColor = { 255, 0, 0,255 };
    if (imageHandler::text)
    {
        // deallocate memory for previous text, if exist
        SDL_DestroyTexture(imageHandler::text);   imageHandler::text = nullptr;
    }

    imageHandler::text = loadText(scoreStr.str().c_str(), textColor);
    SDL_Rect scoreBoard = { 80,300,400 - 80,480 - 400 };
    imageHandler::showImage(imageHandler::text, nullptr, &scoreBoard);
    SDL_Delay(30);

    imageHandler::text = loadText(HighscoreStr.str().c_str(), textColor);
    SDL_Rect HighscoreBoard = { 80,380,440 - 80,480 - 400 };
    imageHandler::showImage(imageHandler::text, nullptr, &HighscoreBoard);
    renderChanges();

    std::ofstream file("HighScore.txt", ios::trunc);
    if (file)
    {
        file << Highscore;
        file.close();
    }
    // wait until user close the program using X button on window
    SDL_Event end;
    bool finalEnd = false;
    while (!finalEnd)
    {
        while (SDL_PollEvent(&end))
        {
            if (end.type == SDL_QUIT) {
                finalEnd = true;
            }
        }
    }
}

void Game::waitForKB()
{
    bool kb = false;
    while (!kb)
    {
        while (SDL_PollEvent(&gameEvents))
        {
            if (gameEvents.key.keysym.sym == SDLK_SPACE || gameEvents.type == SDL_MOUSEBUTTONDOWN)
            {
                kb = true;
            }
            else if (gameEvents.type == SDL_QUIT)
            {
                kb = true;
                gameState = EXIT;
            }
        }
    }
}
