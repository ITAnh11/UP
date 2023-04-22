#include "../HeaderFile/GameMap.h"

bool GAMEMAP::setTiles(const string path)
{
    // Success flag
    bool tilesLoaded = true;

    // The tile offsets
    int x = 0, y = 0;

    // Open the map
    ifstream filemap(path);

    // If the map couldn't be loaded
    if (filemap.fail())
    {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    }
    else
    {
        gTileSet.resize(TOTAL_TILES);
        // Initialize the tiles
        for (int i = 0; i < TOTAL_TILES; ++i)
        {
            // Determines what kind of tile will be made
            int tileType = -1;

            // Read tile from map file
            filemap >> tileType;

            // If the was a problem in reading the map
            if (filemap.fail())
            {
                // Stop loading map
                printf("Error loading map: Unexpected end of file!\n");
                tilesLoaded = false;
                break;
            }
            
            // If the number is a valid tile number
            if ((tileType >= 0) && (tileType <= TOTAL_TILE_SPRITES))
            {
                gTileSet[i] = new Tile(x, y, tileType - 1);
            }
            // If we don't recognize the tile type
            else
            {
                // Stop loading map
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }
            // Move to next tile spot
            x += TILE_WIDTH;

            // If we've gone too far
            if (x >= MAP_WIDTH)
            {
                // Move back
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }
        // Clip the sprite sheet
        if (tilesLoaded)
        {
            for (int i = 0; i < TOTAL_TILE_SPRITES; ++i)
            {
                gTileClips[i].x = i * TILE_WIDTH;
                gTileClips[i].y = 0;
                gTileClips[i].w = TILE_WIDTH;
                gTileClips[i].h = TILE_HEIGHT;
            }
        }
    }

    // Close the file
    filemap.close();

    // If the map was loaded fine
    return tilesLoaded;
}

void GAMEMAP::render()
{
    for (int i = 0; i < TOTAL_TILES; ++i)
    {
        gTileSet[i]->render(gCamera, gTileTexture, gTileClips);
    }
}