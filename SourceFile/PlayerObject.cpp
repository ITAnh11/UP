#include "../HeaderFile/PlayerObject.h"

PlayerObject::PlayerObject()
{
    mRect = {0, 0, 0, 0};
    mFrame = 0;
    mNumberFrame = 1;
    mStatus = IDLE;
    mDirect = RIGHT;
    mInputAction.walk = false;
    mInputAction.jump = false;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::setXY(const int x, const int y)
{
    mRect.x = x;
    mRect.y = y;
}

void PlayerObject::setClip()
{
    for (int i = 0; i < mNumberFrame; ++i)
    {
        mSpriteClips[i].x = i * (mWidth / mNumberFrame);
        mSpriteClips[i].y = 0;
        mSpriteClips[i].w = mWidth / mNumberFrame;
        mSpriteClips[i].h = mHeight;
    }
}

void PlayerObject::renderClips(const int x, const int y)
{
    SDL_Rect *currentClip = &mSpriteClips[mFrame / 20];
    ++mFrame;
    if (mFrame == mNumberFrame *20)
        mFrame = 0;
    if (mDirect == LEFT)
        render(x, y, currentClip, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        render(x, y, currentClip);
}

void PlayerObject::handleMove()
{
}

void PlayerObject::handleInputAction(SDL_Event event)
{
    StatusPlayer nextStatus;
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            mInputAction.walk = true;
            nextStatus = WALK;
            mDirect = LEFT;
            break;

        case SDLK_d:
            mInputAction.walk = true;
            nextStatus = WALK;
            mDirect = RIGHT;
            break;
        case SDLK_SPACE:
            mInputAction.jump = true;
            nextStatus = JUMP;
            break;
        default:
            break;
        }
    }

    if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            mInputAction.walk = false;
            nextStatus = IDLE;
            break;
        case SDLK_d:
            mInputAction.walk = false;
            nextStatus = IDLE;
            break;
        case SDLK_SPACE:
            mInputAction.jump = false;
            break;
        default:
            break;
        }
    }

    if (mInputAction.jump == true || mInputAction.walk == true)
    {
        if (mStatus != nextStatus)
        {
            mFrame = 0;
            mStatus = nextStatus;
            switch (mStatus)
            {
            case WALK:
                loadFromFile("Image/Player/8_PlayerWalk_48x48.png");
                setNumFrame(NUM_FRAMES_WALK);
                setClip();
                break;
            case JUMP:
                loadFromFile("Image/Player/3_player_jump_48x48.png");
                setNumFrame(NUM_FRAMES_JUMP);
                setClip();
                break;
            default:
                loadFromFile("Image/Player/10_Character_Idle_48x48.png");
                setNumFrame(NUM_FRAMES_IDLE);
                setClip();
                break;
            }
        }
    }
    else
    {
        if (mStatus != nextStatus)
        {
            mFrame = 0;
            mStatus = nextStatus;
            loadFromFile("Image/Player/10_Character_Idle_48x48.png");
            setNumFrame(NUM_FRAMES_IDLE);
            setClip();
        }
    }
}
