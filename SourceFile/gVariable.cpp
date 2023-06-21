#include "../HeaderFile/gVariable.h"

BaseObject *gBackground = new BaseObject;
PlayerObject *gPlayer = new PlayerObject;

BaseObject *gTileTexture = new BaseObject;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
vector<Tile *> gTileSet;
SDL_Rect gCamera = {0, MAP_HEIGHT - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
int top_i_have_tile = 54;
int gScores = 0;
int gHighestScores;