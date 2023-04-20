#include "../HeaderFile/Game.h"

bool GAME::initGame()
{
    return true;
}

bool GAME::loadPlayer()
{

    return false;
}

bool GAME::run()
{
    SDL_Event event;
    bool quit = false;
    
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            gPlayer->handleInputAction(event);
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackground->render(0, 0);
        gPlayer->renderClips(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

        SDL_RenderPresent(gRenderer);
    }

    return true;
}