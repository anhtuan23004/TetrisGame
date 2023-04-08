
#include "GameCanvas.h"
#include "Block.h"
#include "soundHandler.h"
#include <SDL_image.h>

// 2 khối được sử dụng 
Block currentBlock; // Lưu trữ khối đang di chuyển
Block nextBlock;    // Lưu trữ khối sắp xuất hiện

GameCanvas canvas; 

Game::Game()
{
    //constructor giá trị mặc định
    gameSurface = nullptr;   gameWindow = nullptr;

    gameState = PLAY;

    score = 0;
}

Game::~Game()
{
    //destructor init to nullptr sau khi đóng bộ nhớ 
    gameSurface = nullptr;    gameRenderer = nullptr;
    gameWindow = nullptr;   font = nullptr;
}

// Hàm thành viên tĩnh , được khai báo bên trong lớp nhưng được định nghĩa bên ngoài lớp
SDL_Renderer* Game::gameRenderer = nullptr;
TTF_Font* Game::font = nullptr;

void Game::fatalError(string error, bool closeProgram)
{
    cout << "Error Occured : " << error << endl; // Nếu đóng chương trình , dọn hệ thống và thoát
    if (closeProgram)
    {
        Game g; //Bởi vì nó là hàm tĩnh , Cần đối tượng để gọi hàm thành viên không tĩnh
        g.cleanSystem();
        cin.get();
        exit(-1);
    }
}

// Nạp văn bản 
SDL_Texture* Game::loadText(string text, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(Game::font, text.c_str(), color); // Đưa chữ ra bề mặt
    SDL_Texture* ret = SDL_CreateTextureFromSurface(gameRenderer, textSurface);    // Chuyển đổi bề mặt thành kết cấu
    SDL_FreeSurface(textSurface);   textSurface = nullptr;    // Bề mặt trống
    return ret;     // Trả về dạng kết cấu chữ
}


void Game::run()
{
    if (!initSystem())   // Hệ thống và thư viện ban đầu
    {
        cout << "Error in INITIALIZING System " << endl; cin.get(); return;
    }
    if (!loadFiles())    // Chạy file và cấp phát bộ nhớ 
    {
        cout << "Error in Loading Files " << endl;  cin.get();  return;
    }

    // Đưa ảnh ra màn hình
    imageHandler::showImage(imageHandler::titleScreenTexture, nullptr, nullptr);
    renderChanges();
    SDL_Delay(1000);

    imageHandler::showImage(imageHandler::newGameTexture, nullptr, nullptr);
    renderChanges();

    gameState = PLAY;     // Bắt đầu game

    waitForKBHit(); // Đợi nhấn nút 

    while (gameState == PLAY)
    {
        gameLoop(); 
    }


    cleanSystem();  // Dọn hệ thống và thoát
}


bool Game::initSystem()
{
    SDL_Init(SDL_INIT_EVERYTHING); 
    IMG_Init(IMG_INIT_PNG);     
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Tạo của sổ , đính lên màn hình ,  tạo màu vẽ cơ bản
    gameWindow = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gameSurface = SDL_GetWindowSurface(gameWindow);
    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);

    return true;  
}

void Game::cleanSystem()
{
    // Giải phóng bộ nhớ
    SDL_FreeSurface(gameSurface);
    SDL_DestroyRenderer(gameRenderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(gameWindow);
    imageHandler::freeAllMemory();
    soundHandler::freeAllSounds();

    // Đóng SDl
    Mix_Quit();  TTF_Quit();  IMG_Quit();  SDL_Quit();
}

// Chạy file , cấp phát bộ nhớ
bool Game::loadFiles()
{
    font = TTF_OpenFont("assets/fonts/neuropol.ttf", 24);
    if (!font || !imageHandler::loadAllImages() || !soundHandler::loadAllSounds())
        return false;
    return true;
}

// Điều khiển game
void Game::handleGameEvents()
{
    while (SDL_PollEvent(&gameEvents))
    {
        switch (gameEvents.type) 
        {
        case SDL_QUIT: // Nếu ấn nút X
            gameState = EXIT; // game EXIT
            break;
        case SDL_KEYDOWN:   // điều khiên bản phím
            if (gameEvents.key.keysym.sym == SDLK_SPACE) // Dấu cách để xoay khối
            {
                // Xóa vị trí của khối
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                // Xoay khối
                currentBlock.rotateBlock();
            }
            else if (gameEvents.key.keysym.sym == SDLK_DOWN) // Khối rơi xuống
            {
 
                // Xóa khối
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                // Nếu không có gì xày ra
                if (!canvas.checkForStopCondition(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
                {
                    soundHandler::playMovementEffect(); // Âm thanh khi di chuyển
                    int newRow = currentBlock.getRowNo();
                    newRow++;                           // Tăng số hàng của khối
                    currentBlock.setRowNo(newRow);  // setter số hàng tăng dần
                }

            }
            else if (gameEvents.key.keysym.sym == SDLK_LEFT)  // Di chuyển khối sang trái
            {

                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                if (canvas.isLeftMovePossible(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
                    currentBlock.moveBlockHoriz(0);
            }
            else if (gameEvents.key.keysym.sym == SDLK_RIGHT)
            {
                canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
                if (canvas.isRightMovePossible(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
                    currentBlock.moveBlockHoriz(1); 
            break;
        }
    }
}
void Game::updateScreen()
{
    // Xóa màn hình , background màu trắng
    SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gameRenderer);

    // Xuất ảnh background
    imageHandler::showImage(imageHandler::bkTexture, nullptr, nullptr);

    // Xóa cả khối hiện tại và tiếp theo
    canvas.clearBlockFromCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());
    canvas.clearBlockFromCanvas(nextBlock.blockPattern, nextBlock.getRowNo(), nextBlock.getColNo());

    // DI chuyển khối đi xuống
    currentBlock.moveBlockDown();

    canvas.copyBlockToCanvas(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo());

    if (canvas.checkForStopCondition(currentBlock.blockPattern, currentBlock.getRowNo(), currentBlock.getColNo()))
    {
        score += 5;   // Nếu khối được đặt xuống
        if (canvas.unifyColor()) // Kiểm tra điều kiện game over
        {
            canvas.showMatrix();    // Ma trận hiện tại
            SDL_Delay(1000);
            gameState = EXIT;     // Game dừng
            return;
        }
        while (canvas.destroyRows())    // Kiểm tra nếu hàng ngang đầy và phá nó
        {
            soundHandler::playDestructionEffect();  // Âm thanh hàng biến mất
            score += 20; 
        }
        currentBlock = nextBlock;
        currentBlock.setRowNo(0);  currentBlock.setColNo(4);    // Thay đổi vị trí của khối hiện tại 
        nextBlock.createNewBlock(23, 18); 
    }

    canvas.copyBlockToCanvas(nextBlock.blockPattern, nextBlock.getRowNo(), nextBlock.getColNo());
    canvas.showMatrix();
    renderScore();

}

void Game::renderChanges()
{
    SDL_RenderPresent(gameRenderer);    // Dán tất cả thay đổi trên màn hình
}

// main game loop
void Game::gameLoop()
{
    soundHandler::playBGM();   
    score = 0;      
    currentBlock.createNewBlock(0, 4);
    nextBlock.createNewBlock(23, 18);
    while (gameState == PLAY)
    {
        handleGameEvents(); 
        updateScreen();     
        renderChanges();
    }
    soundHandler::stopBGM();
    gameOver(); 
}

// Bảng điểm
void Game::renderScore()
{
    stringstream scoreStr;  
    scoreStr << " " << score << " ";
    SDL_Color textColor = { 0,0,0,255 };
    if (imageHandler::text)
    {
        // Giải phóng bộ nhớ
        SDL_DestroyTexture(imageHandler::text);   imageHandler::text = nullptr;
    }
    //  Xuất ảnh ra ngoài màn hình
    imageHandler::text = loadText(scoreStr.str().c_str(), textColor);
    SDL_Rect scoreBoard = { 340,110,440 - 340,150 - 110 };
    imageHandler::showImage(imageHandler::text, nullptr, &scoreBoard);

}

void Game::gameOver()
{
    soundHandler::playGameOverEffect(); // Âm thanh game over
    imageHandler::showImage(imageHandler::transparentTexture, nullptr, nullptr);  // Làm bk trong suốt

    // Tải ảnh game over
    SDL_Rect gameOverRect = { 40,120,440 - 40,380 - 120 };
    imageHandler::showImage(imageHandler::gameOverTexture, nullptr, &gameOverRect);

    // Xuất tổng điểm 
    stringstream scoreStr;
    scoreStr << " SCORE : " << score << " ";
    SDL_Color textColor = { 255, 255, 0,255 };
    if (imageHandler::text)
    {
        // Giải phóng bộ nhớ
        SDL_DestroyTexture(imageHandler::text);   imageHandler::text = nullptr;
    }
    imageHandler::text = loadText(scoreStr.str().c_str(), textColor);
    SDL_Rect scoreBoard = { 80,400,400 - 80,480 - 400 };
    imageHandler::showImage(imageHandler::text, nullptr, &scoreBoard);

    renderChanges();

    // Đợi đến khi người dùng đóng chương trình
    SDL_Event ev;
    bool finalEnd = false;
    while (!finalEnd)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
                finalEnd = true;
        }
    }
}

void Game::waitForKBHit()
{
    bool cont = false;
    // Đợi phím hoặc đóng chương trình
    while (!cont)
    {
        while (SDL_PollEvent(&gameEvents))
        {
            if (gameEvents.type == SDL_KEYDOWN)
                cont = true;
            else if (gameEvents.type == SDL_QUIT)
            {
                cont = true;
                gameState = EXIT;
            }
        }
    }
}


