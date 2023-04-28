#include "../HeaderFile/Game.h"
#include "../HeaderFile/TextObject.h"

TextObject gTextScores;
TextObject gTextHighestScores;

void GAME::loadSave()
{
    ifstream fi("savegame.txt");
    if (fi)
    {
        string s;
        getline(fi, s);
        fi >> gHighestScores;
    }
}

bool GAME::initGame()
{
    bool success = true;

    loadSave();
    gScores = 0;

    if (!GAMEMAP::setTiles("Image/map/map.txt"))
    {
        success = false;
        printf("Failed to set tiles\n");
    }

    // Open the font
    gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_SMALL);
    if (gFont)
    {

        SDL_Color textColor = {255, 150, 0};
        gTextScores.loadFromRenderedText("Scores : " + to_string(gScores), textColor);
        gTextScores.setPos(0, 0);
    }

    gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_MEDIUM);
    if (gFont)
    {
        // Render text
        SDL_Color textColor = {255, 255, 0};
        gTextHighestScores.loadFromRenderedText("*********************************************Highest scores: " + to_string(gHighestScores) + " *********************************************", textColor);
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

    gPlayer->setXY(SCREEN_WIDTH / 2, MAP_HEIGHT - TILE_HEIGHT - gPlayer->getBox().h - 10);

    int indexReturn = -1;
    int i_tile_return = -1;
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
        gPlayer->doPlayer(gTileSet, gCamera, indexReturn, i_tile_return, gScores);
        gPlayer->handleMove();
        gPlayer->setCamera(gCamera);

        // update map
        GAMEMAP::updateRandom(i_tile_return, indexReturn, gCamera);

        StatusPlayer stPlayer = gPlayer->getStatus();
        if (stPlayer == DEATH)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "UP", "You Die", NULL);
            quit = true;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackground->render(0, 0);

        GAMEMAP::render();

        gPlayer->renderClips(gCamera);

        SDL_Color textColor = {255, 150, 0};
        gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_SMALL);
        gTextScores.loadFromRenderedText("Scores : " + to_string(gScores), textColor);
        gTextScores.render(0, 0);

        if (gScores <= gHighestScores && gHighestScores <= gScores + SCREEN_HEIGHT)
        {
            gTextHighestScores.render(SCREEN_WIDTH / 2 - gTextHighestScores.getWidth() / 2, SCREEN_HEIGHT - (gHighestScores - gScores));
        }

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return true;
}

void GAME::createSaveGame()
{
    if (gScores > gHighestScores)
        gHighestScores = gScores;
    ofstream fo("savegame.txt");
    if (fo)
    {
        fo << "Highest scores:\n";
        fo << gHighestScores;
    }
}