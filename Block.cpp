#include "Block.h"
#include "soundHandler.h"
#include "GameCanvas.h"

int blockPatterns[7][4][4] =
{
    {
        // I
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
    },
    {
        // O
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    {
        // T
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,1,0,0}
    },
    {
        // L
        {0,0,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0}
    },
    {
        // L-Mirrored
        {0,0,0,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0}
    },
    {
        // Z
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0}
    },
    {
        // Z-Mirrored
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0}
    }
};



Block::Block()
{
    tileType = rowNo = colNo = 0;
}

<<<<<<< HEAD
Block::~Block() {}

void Block::createNewBlock(int r, int c)
{
    int pattern = rand() % 7;
    tileType = rand() % 5 + 2;
    rowNo = r;   colNo = c;
=======
Block::~Block(){}

void Block::createNewBlock(int r, int c)
{
    int pattern = rand() % 7;   
    tileType = rand() % 5 + 2;    
    rowNo = r;   colNo = c; 
>>>>>>> afeb2a6 ('init')

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blockPattern[i][j] = blockPatterns[pattern][i][j] * tileType;
        }
    }
}
void Block::rotateBlock()
{
<<<<<<< HEAD
    soundHandler::playMovementEffect();
    int copyBlock[4][4];
=======
    soundHandler::playMovementEffect(); 
    int copyBlock[4][4];   
>>>>>>> afeb2a6 ('init')

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            copyBlock[i][j] = blockPattern[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            blockPattern[i][j] = copyBlock[j][4 - 1 - i];
        }
    }

    if (colNo < 0)
    {
        colNo = 0;
        int minC = 5;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (blockPattern[i][j] > 0)
                {
                    if (j < minC)
                        minC = j;
                }
            }
        }
        colNo -= minC;
    }
    else if (colNo + 4 > TET_COLS - 1)
    {
        colNo = TET_COLS - 1 - 4;
        int maxC = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (blockPattern[i][j] > 0)
                {
                    if (j >= maxC)
                    {
                        maxC = j;
                    }
                }
            }
        }
        maxC = 3 - maxC;
        colNo += maxC;

    }
}
void Block::moveBlockDown()
{
    static unsigned long long int i = 0;
<<<<<<< HEAD
    if (i++ % 40 == 0)
    {
        soundHandler::playMovementEffect();
        rowNo++;
=======
    if (i++ % 40 == 0)   
    {
        soundHandler::playMovementEffect(); 
        rowNo++;                
>>>>>>> afeb2a6 ('init')
    }
}
void Block::moveBlockHoriz(int dir)
{
<<<<<<< HEAD
    soundHandler::playMovementEffect();
    if (dir == 0)
    {
        colNo--;
    }
    else if (dir == 1)
=======
    soundHandler::playMovementEffect(); 
    if (dir == 0)  
    {
        colNo--;
    }
    else if (dir == 1)     
>>>>>>> afeb2a6 ('init')
    {
        colNo++;
    }
}

int Block::getRowNo()
{
    return rowNo;
}
int Block::getColNo()
{
    return colNo;
}
void Block::setRowNo(int r)
{
    rowNo = r;
}
void Block::setColNo(int c)
{
    colNo = c;
}
int Block::getTileType()
{
    return tileType;
}
void Block::setTileType(int type)
{
    tileType = type;
}