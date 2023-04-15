#ifndef BLOCK_H
#define BLOCK_H

#include "Game.h"


class Block
{
public:
    Block();
    virtual ~Block();

<<<<<<< HEAD
    int blockPattern[4][4];

    void createNewBlock(int r, int c);
    void rotateBlock();
    void moveBlockDown();
    void moveBlockHoriz(int dir);


=======
    int blockPattern[4][4]; 

    void createNewBlock(int r, int c);       
    void rotateBlock();     
    void moveBlockDown();   
    void moveBlockHoriz(int dir);   

    
>>>>>>> afeb2a6 ('init')
    int getRowNo();
    int getColNo();
    void setRowNo(int);
    void setColNo(int);
    int getTileType();
    void setTileType(int);

protected:

private:
<<<<<<< HEAD
    int rowNo, colNo;
    int tileType;
=======
    int rowNo, colNo;        
    int tileType;   
>>>>>>> afeb2a6 ('init')
};


#endif // BLOCK_H