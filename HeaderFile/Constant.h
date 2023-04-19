#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

#endif