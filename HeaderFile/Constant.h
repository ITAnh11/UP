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

using namespace std;

// Screen
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

// Player
const int NUM_FRAMES_IDLE = 10;
const int NUM_FRAMES_JUMP = 3;
const int NUM_FRAMES_MOVE = 8;
const int SPEED_MOVE = 4;
const int SPEED_JUMP = 6;
const int MAX_JUMP_HEIGHT = SPEED_JUMP * 100;

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

const int TILE_SPECIAL_BOX = 9;
const int TILE_DIE_BEGIN = 3;
const int TILE_DIE_END = 5;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

// Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);
#endif