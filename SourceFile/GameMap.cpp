#include "../HeaderFile/GameMap.h"

// khởi tạo map ban đầu, map lưu dưới dạng mảng 1 chiều
// set vị trí cho các tile
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

    randomTopMap(0);

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

// cập nhật map sau khi va chạm tại vị trí index
void GAMEMAP::updateCollision(int &index)
{
    // -1 là khi không va chạm
    if (index == -1)
        return;

    int typeTile = gTileSet[index]->getType();

    // special_box bị xóa đi
    if (typeTile == TILE_SPECIAL_BOX)
    {
        gTileSet[index]->free();
    }
    // mây bị xóa đi
    else if (TILE_CLOUD_BEGIN <= typeTile && typeTile <= TILE_CLOUD_END)
    {
        gTileSet[index]->free();
        if (typeTile == TILE_CLOUD_END)
            index -= 2;
        else if (typeTile == TILE_CLOUD_END - 1)
            index -= 1;
        for (int i = 0; i <= 2; ++i)
        {
            gTileSet[index + i]->free();
        }
    }
    else if (TILE_GROUND_BEGIN <= typeTile && typeTile <= TILE_GROUND_END)
    {
        // ngẫu nhiên đất biến thành mây
        int prob = randomBetween(0, PROBABILITY_TILE_CLOUD);
        if (prob == PROBABILITY_TILE_CLOUD)
        {
            if (typeTile == TILE_GROUND_END)
                index -= 2;
            else if (typeTile == TILE_GROUND_END - 1)
                index -= 1;
            for (int i = 0; i <= 2; ++i)
            {
                gTileSet[index + i]->set(TILE_CLOUD_BEGIN + i);
            }
        }
    }

    index = -1;
}

// đẩy map xuống numRows hàng từ vị trí va chạm
void GAMEMAP::pushMapDown(SDL_Rect &camera, int &numRows)
{
    int i_tileEnd_camera = (camera.y + camera.h) / TILE_HEIGHT;
    i_tileEnd_camera += 2;
    int i_distance = NUM_TILE_ROWS - i_tileEnd_camera - 1;

    if (i_distance > 0)
    {
        // xóa các tile trước khi đẩy map xuống, tránh lỗi map
        for (int i = NUM_TILE_ROWS - 1; i >= i_distance; --i)
        {
            for (int j = 0; j < NUM_TILE_COLS; ++j)
            {
                gTileSet[i * NUM_TILE_COLS + j]->set(-1);
                gTileSet[i * NUM_TILE_COLS + j]->set(gTileSet[(i - i_distance) * NUM_TILE_COLS + j]->getType());
            }
        }

        // đẩy map xuống
        for (int i = 0; i < i_distance; ++i)
        {
            for (int j = 0; j < NUM_TILE_COLS; ++j)
            {
                gTileSet[i * NUM_TILE_COLS + j]->set(-1);
            }
        }

        // đưa nhân vật xuống theo map
        gPlayer->setXY(gPlayer->getRect().x, gPlayer->getRect().y + i_distance * TILE_HEIGHT);
        gPlayer->setCamera(camera);
        gPlayer->setRectangle();

        numRows = i_distance;
    }
}

// khởi tạo ngẫu nhiên phần trên của map sau khi đẩy xuống numRows hàng
void GAMEMAP::randomTopMap(const int &numRows)
{
    if (numRows == -1) return;
    int i = top_i_have_tile - VAL_I_NEXT_HAVE_TILE + numRows;

    for (; i >= 0; i -= VAL_I_NEXT_HAVE_TILE)
    {
        int j_have_tile = randomBetween(0, NUM_TILE_COLS - 1 - 3);
        int prob = randomBetween(0, PROBABILITY_TILE_CLOUD);
        if (prob == PROBABILITY_TILE_CLOUD)
        {
            for (int j = 0; j < 3; ++j)
            {
                gTileSet[i * NUM_TILE_COLS + j_have_tile + j]->set(TILE_CLOUD_BEGIN + j);
            }

            int l = j_have_tile - 1;
            int r = j_have_tile + 3;
            if (l - 2 > NUM_TILE_COLS - r - 3)
                j_have_tile = randomBetween(0, l - 2);
            else
                j_have_tile = randomBetween(r, NUM_TILE_COLS - 1 - 3);

            for (int j = 0; j < 3; ++j)
            {
                gTileSet[i * NUM_TILE_COLS + j_have_tile + j]->set(TILE_GROUND_BEGIN + j);
            }
            if (i - 1 >= 0)
            {
                prob = randomBetween(0, PROBABILITY_TILE_SPECIAL_BOX);
                if (prob == PROBABILITY_TILE_SPECIAL_BOX)
                {
                    gTileSet[(i - 1) * NUM_TILE_COLS + j_have_tile + 1]->set(TILE_SPECIAL_BOX);
                }
            }
        }
        else
        {
            for (int j = 0; j < 3; ++j)
            {
                gTileSet[i * NUM_TILE_COLS + j_have_tile + j]->set(TILE_GROUND_BEGIN + j);
            }
            if (i - 1 >= 0)
            {
                prob = randomBetween(0, PROBABILITY_TILE_THORN);
                if (prob == PROBABILITY_TILE_THORN)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        gTileSet[(i - 1) * NUM_TILE_COLS + j_have_tile + j]->set(TILE_THORN_BEGIN + j);
                    }
                }
                else
                {
                    prob = randomBetween(0, PROBABILITY_TILE_SPECIAL_BOX);
                    if (prob == PROBABILITY_TILE_SPECIAL_BOX)
                    {
                        gTileSet[(i - 1) * NUM_TILE_COLS + j_have_tile + 1]->set(TILE_SPECIAL_BOX);
                    }
                }
            }
        }
    }
    top_i_have_tile = i + VAL_I_NEXT_HAVE_TILE;
}

void GAMEMAP::updateRandom(int &i_tile, int &index, SDL_Rect &camera)
{
    updateCollision(index);
    
    if (i_tile == -1)
        return;

    SDL_Rect oldCamera = camera;
    int numRows = -1;
    pushMapDown(camera, numRows);
    randomTopMap(numRows);

    i_tile = -1;
}