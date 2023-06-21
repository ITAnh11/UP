#include "../HeaderFile/Game.h"
#include "../HeaderFile/TextObject.h"

TextObject gTextScores;
TextObject gTextHighestScores;
TextObject gYouDIE;
TextObject gPlay;
TextObject gQuit;
TextObject gUP;

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

    top_i_have_tile = 54;
    if (!GAMEMAP::setTiles("Image/map/map.txt"))
    {
        success = false;
        printf("Failed to set tiles\n");
    }

    SDL_Color textColor;
    // Open the font
    gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_SMALL);
    if (gFont)
    {
        textColor = {255, 150, 0};
        gTextScores.loadFromRenderedText("Scores : " + to_string(gScores), textColor);
        gTextScores.setPos(0, 0);
    }

    gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_MEDIUM);
    if (gFont)
    {
        textColor = {255, 115, 20};
        gTextHighestScores.loadFromRenderedText("*********************************************Highest scores: " + to_string(gHighestScores) + " *********************************************", textColor);
    }

    gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_MEDIUM);
    if (gFont)
    {
        textColor = {0, 255, 65};
        gPlay.loadFromRenderedText("PLAY", textColor);
        gPlay.setPos(0, MAP_HEIGHT - 352);

        textColor = {255, 0, 0};
        gQuit.loadFromRenderedText("QUIT", textColor);
        gQuit.setPos(SCREEN_WIDTH - gQuit.getWidth(), MAP_HEIGHT - 352);
    }

    gFont = TTF_OpenFont("font/BagelFatOne-Regular.ttf", TEXT_SIZE_BIG * 2);
    if (gFont)
    {
        textColor = {243, 0, 243};
        gUP.loadFromRenderedText("UP", textColor);
    }

    // init player
    loadPlayer();

    return success;
}

bool GAME::loadPlayer()
{
    if (!gPlayer->loadFromFile("Image/Player/10_Character_Idle_48x48.png"))
    {
        printf("Failed to load player\n");
        return false;
    }
    else
    {
        gPlayer->reset();
        gPlayer->setNumFrame(NUM_FRAMES_IDLE);
        gPlayer->setClip();
        gPlayer->setScale(2);
        gPlayer->setRectangle();
        gPlayer->setXY(SCREEN_WIDTH / 2, MAP_HEIGHT - TILE_HEIGHT - gPlayer->getBox().h - 10);
    }

    return true;
}

bool GAME::menuGame(bool &is_play)
{
    if (!is_play)
    {
        gUP.render(SCREEN_WIDTH / 2 - gUP.getWidth() / 2, SCREEN_HEIGHT / 2 - gUP.getHeight() / 2 - 250 - (gCamera.y - MAP_HEIGHT + SCREEN_HEIGHT) / 4);

        gPlay.render(0, 256 - (gCamera.y - MAP_HEIGHT + SCREEN_HEIGHT));

        gQuit.render(SCREEN_WIDTH - gQuit.getWidth(), 256 - (gCamera.y - MAP_HEIGHT + SCREEN_HEIGHT));

        if (checkCollision(gQuit.getPos(), gPlayer->getBox()))
            return false;
        if (checkCollision(gPlay.getPos(), gPlayer->getBox()))
        {
            is_play = true;
        }
    }
    return true;
}

GAME::StatusGame GAME::run()
{
    SDL_Event event;

    Uint32 frameStart;
    int frameTime;

    int indexReturn = -1;
    int i_tile_return = -1;

    bool is_play = false;

    while (true)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return QUIT;
            }
            gPlayer->handleInputAction(event);
        }

        // player
        gPlayer->doPlayer(gTileSet, gCamera, indexReturn, i_tile_return, gScores);
        gPlayer->handleMove();
        gPlayer->setCamera(gCamera);

        // update map
        GAMEMAP::updateRandom(i_tile_return, indexReturn, gCamera);

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        StatusPlayer stPlayer = gPlayer->getStatus();

        if (stPlayer == DEATH)
        {
            gameOver();
            return PLAY;
        }

        gBackground->render(0, 0);

        GAMEMAP::render();

        if (!menuGame(is_play))
            return QUIT;

        gPlayer->renderClips(gCamera);

        if (is_play)
        {
            renderScore();
        }

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return QUIT;
}

void GAME::renderScore()
{
    SDL_Color textColor = {255, 150, 0};
    gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_SMALL);
    gTextScores.loadFromRenderedText("Scores : " + to_string(gScores), textColor);
    gTextScores.render(0, 0);

    if (gScores <= gHighestScores && gHighestScores <= gScores + SCREEN_HEIGHT)
    {
        if (gScores <= SCREEN_HEIGHT * 3 / 2)
        {
            gTextHighestScores.render(SCREEN_WIDTH / 2 - gTextHighestScores.getWidth() / 2, SCREEN_HEIGHT - gHighestScores - (gCamera.y - MAP_HEIGHT + SCREEN_HEIGHT));
        }
        else
            gTextHighestScores.render(SCREEN_WIDTH / 2 - gTextHighestScores.getWidth() / 2, SCREEN_HEIGHT - (gHighestScores - gScores));
    }
}

void GAME::gameOver()
{
    bool quit = false;

    Uint32 frameStart;
    int frameTime;

    int size = 1;

    while (!quit)
    {
        frameStart = SDL_GetTicks();

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackground->render(0, 0);

        GAMEMAP::render();

        gPlayer->renderClips(gCamera);

        SDL_Color textColor;

        textColor = {255, 0, 0};
        gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", size);
        gYouDIE.loadFromRenderedText("You Die", textColor);
        gYouDIE.render(SCREEN_WIDTH / 2 - gYouDIE.getWidth() / 2, SCREEN_HEIGHT / 2 - 200);
        ++size;

        textColor = {249, 249, 0};
        gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_MEDIUM);
        gTextHighestScores.loadFromRenderedText("Highest scores : " + to_string(gHighestScores), textColor);
        gTextHighestScores.render(SCREEN_WIDTH / 2 - gTextHighestScores.getWidth() / 2, SCREEN_HEIGHT / 2 - 100);

        gFont = TTF_OpenFont("font/ChakraPetch-Regular.ttf", TEXT_SIZE_SMALL);
        gTextScores.loadFromRenderedText("Your scores : " + to_string(gScores), textColor);
        gTextScores.render(SCREEN_WIDTH / 2 - gTextScores.getWidth() / 2, SCREEN_HEIGHT / 2);

        SDL_RenderPresent(gRenderer);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        if (size == TEXT_SIZE_BIG)
            quit = true;
    }
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