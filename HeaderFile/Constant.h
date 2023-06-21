#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <time.h>

using namespace std;

// Screen
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

// The dimensions of map
const int MAP_WIDTH = SCREEN_WIDTH;
const int MAP_HEIGHT = SCREEN_HEIGHT * 4;

// Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int NUM_TILE_ROWS = MAP_HEIGHT / TILE_HEIGHT;
const int NUM_TILE_COLS = MAP_WIDTH / TILE_WIDTH;
const int TOTAL_TILES = MAP_HEIGHT * MAP_WIDTH / (TILE_HEIGHT * TILE_WIDTH);
const int TOTAL_TILE_SPRITES = 10;

const int TILE_GROUND_BEGIN = 0;
const int TILE_GROUND_END = 2;
const int TILE_THORN_BEGIN = 3;
const int TILE_THORN_END = 5;
const int TILE_CLOUD_BEGIN = 6;
const int TILE_CLOUD_END = 8;
const int TILE_SPECIAL_BOX = 9;

const int PROBABILITY_TILE_GROUND = 1;
const int PROBABILITY_TILE_CLOUD = 4;
const int PROBABILITY_TILE_THORN = 5;
const int PROBABILITY_TILE_SPECIAL_BOX = 5;

const int VAL_I_NEXT_HAVE_TILE = 6;

// Player
const int NUM_FRAMES_IDLE = 10;
const int NUM_FRAMES_JUMP = 3;
const int NUM_FRAMES_MOVE = 8;
const int SPEED_MOVE = 4;
const int SPEED_JUMP = TILE_HEIGHT / 4;
const int SPECIAL_SPEED_JUMP = TILE_HEIGHT / 2;
const int MAX_JUMP_HEIGHT = SPEED_JUMP * 100;
const int SPECIAL_MAX_JUMP_HEIGHT = SPECIAL_SPEED_JUMP * 100;

// Size Text
const int TEXT_SIZE_BIG = 80;
const int TEXT_SIZE_MEDIUM = 40;
const int TEXT_SIZE_SMALL = 20;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

extern TTF_Font *gFont;

// Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);
int randomBetween(const int a, const int b);

#endif

