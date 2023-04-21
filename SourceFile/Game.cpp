#include "../HeaderFile/Game.h"

bool GAME::initGame()
{
    bool success = true;

    if (!GAMEMAP::setTiles("Image/map/map.txt"))
    {
        success = false;
        printf("Failed to set tiles\n");
    }
    return success;
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

    gPlayer->setXY(SCREEN_WIDTH / 2, MAP_HEIGHT - gPlayer->getHeight() - 100);

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
        // move player
        gPlayer->doPlayer();
        gPlayer->handleMove();
        gPlayer->setCamera(gCamera);

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackground->render(0, 0);

        GAMEMAP::render();

        gPlayer->renderClips(gCamera);

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return true;
}