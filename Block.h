#ifndef BLOCK_H
#define BLOCK_H

#include "Game.h"


class Block
{
public:
    Block();
    virtual ~Block();

    int blockPattern[4][4];

    void createNewBlock(int r, int c);
    void rotateBlock();
    void moveBlockDown();
    void moveBlockHoriz(int dir);


    int getRowNo();
    int getColNo();
    void setRowNo(int);
    void setColNo(int);
    int getTileType();
    void setTileType(int);

protected:

private:
    int rowNo, colNo;
    int tileType;
};


#endif // BLOCK_H