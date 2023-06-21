#ifndef GAME_H_
#define GAME_H_

#include "Constant.h"
#include "gVariable.h"
#include "GameMap.h"

namespace GAME
{
    void loadSave();
    bool initGame();
    bool loadPlayer();
    bool run();
    void gameOver();
    void createSaveGame();
};

#endif