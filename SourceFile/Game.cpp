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

    Uint32 frameStart;
    int frameTime;

    gPlayer->setXY(SCREEN_WIDTH / 2, SCREEN_HEIGHT - gPlayer->getHeight() - 100);

    while (!quit)
    {
        frameStart = SDL_GetTicks();

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

        gPlayer->doPlayer();
        gPlayer->handleMove();
        gPlayer->renderClips(gPlayer->getRect().x, gPlayer->getRect().y);

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return true;
}