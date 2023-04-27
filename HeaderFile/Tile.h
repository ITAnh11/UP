#ifndef TILE_H_
#define TILE_H_

#include "Constant.h"
#include "BaseObject.h"

// The tile
class Tile
{
public:
    // Initializes position and type
    Tile(int x, int y, int tileType);

    // Shows the tile
    void render(SDL_Rect &camera, BaseObject *gTileTexture, SDL_Rect *gTileClips);

    void set(const int tileType) { mType = tileType; }

    // Get the tile type
    int getType();

    // Get the collision box
    SDL_Rect getBox();

    void free();

private:
    // The attributes of the tile
    SDL_Rect mBox;

    // The tile type
    int mType;
};

#endif