#include "../HeaderFile/gVariable.h"

BaseObject *gBackground = new BaseObject;
PlayerObject *gPlayer = new PlayerObject;

BaseObject *gTileTexture = new BaseObject;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
vector<Tile *> gTileSet;
SDL_Rect gCamera = {0, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT};
int top_i_have_tile = 73;
int gScores = 0;
int gHighestScores;