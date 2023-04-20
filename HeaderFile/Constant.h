#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>

using namespace std;

//Screen
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

//Player
const int NUM_FRAMES_IDLE = 10;
const int NUM_FRAMES_JUMP = 3;
const int NUM_FRAMES_WALK = 8;
const int JUMP_HEIGHT = 100;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

#endif