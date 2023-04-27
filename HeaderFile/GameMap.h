#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "Constant.h"
#include "gVariable.h"

namespace GAMEMAP
{
    // Sets tiles from tile map
    bool setTiles(const string path);

    // Render map
    void render();

    void updateCollision(int &index);

    void pushMapDown(SDL_Rect &camera, int &numRows);
    void randomTopMap(const int &numRows);
    void updateRandom(int &i_tile, int &index, SDL_Rect &camera);
}

#endif