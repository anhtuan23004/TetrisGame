#ifndef TILES_H
#define TILES_H

#include "Game.h"

#define TILE_BLACK 1
#define TILE_RED 2
#define TILE_GREEN 3
#define TILE_BLUE 4
#define TILE_ORANGE 5
#define TILE_VOILET 6

class Tiles
{
public:
    Tiles();
    virtual ~Tiles();

    static SDL_Rect tilesSrcRects[7];

protected:

private:
};
#endif // TILES_H