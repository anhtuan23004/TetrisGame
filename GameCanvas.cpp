#include "GameCanvas.h"

GameCanvas::GameCanvas()
{
    for (int i = 0; i < CANVAS_ROWS; i++)
        for (int j = 0; j < CANVAS_COLS; j++)
            canvasMatrix[i][j] = 0;
}

<<<<<<< HEAD
GameCanvas::~GameCanvas() {}
=======
GameCanvas::~GameCanvas(){}
>>>>>>> afeb2a6 ('init')

void GameCanvas::showMatrix()
{
    for (int i = 0; i < CANVAS_ROWS; i++)
    {
        for (int j = 0; j < CANVAS_COLS; j++)
        {
<<<<<<< HEAD
            if (canvasMatrix[i][j] != 0)
=======
            if (canvasMatrix[i][j] != 0) 
>>>>>>> afeb2a6 ('init')
            {
                SDL_Rect dest = { j * TILE_DIM,i * TILE_DIM,TILE_DIM,TILE_DIM };
                imageHandler::showImage(imageHandler::tiles, &Tiles::tilesSrcRects[canvasMatrix[i][j]], &dest);
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
            if (block[i][j] != 0)
            {

<<<<<<< HEAD
                canvasMatrix[r + i][c + j] = block[i][j];
=======
                canvasMatrix[r + i][c + j] = block[i][j]; 
>>>>>>> afeb2a6 ('init')
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
<<<<<<< HEAD
            if (block[i][j] != 0)
=======
            if (block[i][j] != 0)  
>>>>>>> afeb2a6 ('init')
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
<<<<<<< HEAD
            if (block[i][j] != 0)
=======
            if (block[i][j] != 0)  
>>>>>>> afeb2a6 ('init')
            {
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
<<<<<<< HEAD
                if (i == 0)
=======
                if (i == 0)        
>>>>>>> afeb2a6 ('init')
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
<<<<<<< HEAD
                filledTiles++;
        }
        if (filledTiles == TET_COLS)
=======
                filledTiles++;  
        }
        if (filledTiles == TET_COLS)   
>>>>>>> afeb2a6 ('init')
        {
            for (int a = i; a >= 1; a--)
            {
                for (int b = 0; b < TET_COLS; b++)
                    canvasMatrix[a][b] = canvasMatrix[a - 1][b];
            }
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
<<<<<<< HEAD
            if (block[i][j] != 0)
=======
            if (block[i][j] != 0) 
>>>>>>> afeb2a6 ('init')
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
<<<<<<< HEAD
            if (block[i][j] != 0)
            {
                if (canvasMatrix[r + i][c + j + 1] == 1 || c + j == TET_COLS - 1)
=======
            if (block[i][j] != 0) 
            {
                if (canvasMatrix[r + i][c + j + 1] == 1 || c + j == TET_COLS - 1)  
>>>>>>> afeb2a6 ('init')
                    return false;
            }
        }
    }
    return true;
}