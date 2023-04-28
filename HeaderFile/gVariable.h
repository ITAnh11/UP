#ifndef G_VARIABLE_H_
#define G_VARIABLE_H_

#include "Constant.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "Tile.h"

extern BaseObject *gBackground;
extern PlayerObject *gPlayer;
extern BaseObject *gTileTexture;
extern SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
extern vector<Tile *> gTileSet;
extern SDL_Rect gCamera;
extern int top_i_have_tile;
extern int gScores;
extern int gHighestScores;

#endif