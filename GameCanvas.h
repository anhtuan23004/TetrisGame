#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include "Game.h"
#include "Tiles.h"
#include "imageHandler.h"

#define CANVAS_ROWS 30
#define CANVAS_COLS 24
#define TET_ROWS  30
#define TET_COLS  15


class GameCanvas
{
public:
    GameCanvas();
    virtual ~GameCanvas();

<<<<<<< HEAD
    void showMatrix();
    bool checkForStopCondition(int block[4][4], int r, int c);
    bool destroyRows();
    void copyBlockToCanvas(int block[4][4], int r, int c);
    void clearBlockFromCanvas(int block[4][4], int r, int c);
    bool isLeftMovePossible(int block[4][4], int r, int c);
    bool isRightMovePossible(int block[4][4], int r, int c);
    bool unifyColor();
=======
    void showMatrix();      
    bool checkForStopCondition(int block[4][4], int r, int c);   
    bool destroyRows();                     
    void copyBlockToCanvas(int block[4][4], int r, int c);    
    void clearBlockFromCanvas(int block[4][4], int r, int c); 
    bool isLeftMovePossible(int block[4][4], int r, int c);   
    bool isRightMovePossible(int block[4][4], int r, int c);  
    bool unifyColor();      
>>>>>>> afeb2a6 ('init')

protected:

private:
    int canvasMatrix[30][24];       // our canvas matrix
};

#endif // GAMECANVAS_H