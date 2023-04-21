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
}

#endif