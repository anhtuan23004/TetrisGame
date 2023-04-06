#include "GameCanvas.h"

GameCanvas::GameCanvas()
{
    for (int i = 0; i < CANVAS_ROWS; i++)
        for (int j = 0; j < CANVAS_COLS; j++)
            canvasMatrix[i][j] = 0;
}

GameCanvas::~GameCanvas(){}

void GameCanvas::showMatrix()
{
    for (int i = 0; i < CANVAS_ROWS; i++)
    {
        for (int j = 0; j < CANVAS_COLS; j++)
        {
            if (canvasMatrix[i][j] != 0)
            {
                SDL_Rect dest = { j * TILE_DIM,i * TILE_DIM,TILE_DIM,TILE_DIM };
                if (imageHandler::tilesTexture == nullptr)
                    cout << "HELLO";
                imageHandler::showImage(imageHandler::tilesTexture, &Tiles::tilesSrcRects[canvasMatrix[i][j]], &dest);
            }
        }
    }
}
void GameCanvas::copyBlockToCanvas(int block[4][4], int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] != 0)  // Chỉ sao chép mẫu và không có số 0 trong mẫu
            {

                canvasMatrix[r + i][c + j] = block[i][j]; // Ma trận chứ vị trí của khối
            }
        }
    }
}
void GameCanvas::clearBlockFromCanvas(int block[4][4], int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] != 0) 
                canvasMatrix[r + i][c + j] = 0;
        }
    }
}

bool GameCanvas::checkForStopCondition(int block[4][4], int r, int c)
{
    bool collided = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] != 0)
            {
                // Nếu nó xuống cuối cùng hoặc ô đen ở dưới
                if (r + i >= 29 || (canvasMatrix[r + i + 1][j + c] == 1))
                    collided = true;
            }
        }
    }
    return collided;
}
bool GameCanvas::unifyColor()
{
    bool isTouhedUp = false;
    for (int i = 0; i < CANVAS_ROWS; i++)
    {
        for (int j = 0; j < CANVAS_COLS; j++)
        {
            if (canvasMatrix[i][j] != 0)
            {
                canvasMatrix[i][j] = 1;
                if (i == 0)        // Kiểm tra đầy hay chưa
                    isTouhedUp = true;
            }
        }
    }
    return isTouhedUp;
}
bool GameCanvas::destroyRows()
{
    bool isRowDestroyed = false;
    for (int i = TET_ROWS - 1; i >= 1; i--)
    {
        int filledTiles = 0;
        for (int j = 0; j < TET_COLS; j++)
        {
            if (canvasMatrix[i][j] == 1)
                filledTiles++;  // Đếm số ô đen 1 hàng
        }
        if (filledTiles == TET_COLS)  
        {
            // Di chuyển tất cả hàng ngang
            for (int a = i; a >= 1; a--)
            {
                for (int b = 0; b < TET_COLS; b++)
                    canvasMatrix[a][b] = canvasMatrix[a - 1][b];
            }
            // Biến hàng trên cùng thành số 0
            for (int c = 0; c < TET_COLS; c++)
                canvasMatrix[0][c] = 0;

            isRowDestroyed = true;
            break;
        }
    }
    return isRowDestroyed;
}
bool GameCanvas::isLeftMovePossible(int block[4][4], int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] != 0)  // Nếu chạm viền hoặc ô màu đen dừng lại
            {
                if (canvasMatrix[r + i][c + j - 1] == 1 || c + j == 0)
                    return false;
            }
        }
    }
    return true;
}
bool GameCanvas::isRightMovePossible(int block[4][4], int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] != 0)  
            {
                if (canvasMatrix[r + i][c + j + 1] == 1 || c + j == TET_COLS - 1)  // Nếu chạm vào viền hoặc ô màu đen
                    return false;
            }
        }
    }
    return true;
}
