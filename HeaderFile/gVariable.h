#ifndef G_VARIABLE_H_
#define G_VARIABLE_H_

#include "Constant.h"
#include "BaseObject.h"
#include "PlayerObject.h"
#include "Tile.h"

extern TTF_Font *gFont;

extern BaseObject *gBackground;
extern PlayerObject *gPlayer;
extern BaseObject *gTileTexture;
extern SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
extern Tile *gTileSet[TOTAL_TILES];
extern SDL_Rect gCamera;

#endif