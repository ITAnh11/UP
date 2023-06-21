#ifndef GAME_H_
#define GAME_H_

#include "Constant.h"
#include "gVariable.h"
#include "GameMap.h"

namespace GAME
{
    enum StatusGame
    {
        QUIT,
        PLAY,
    };

    void loadSave();
    bool initGame();
    bool loadPlayer();
    bool menuGame(bool &is_play);
    StatusGame run();
    void renderScore();
    void gameOver();
    void createSaveGame();

    void free();
};

#endif