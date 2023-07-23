#include "../HeaderFile/PlayerObject.h"

// sound
Mix_Chunk *gSJump = NULL;
Mix_Chunk *gSTakeBox = NULL;
Mix_Chunk *gSDie = NULL;

PlayerObject::PlayerObject()
{
    mRect = {0, 0, 0, 0};
    mFrame = 0;
    mNumberFrame = 1;
    mInputAction.moveRight = false;
    mInputAction.moveLeft = false;
    mInputAction.jump = false;
    mJumpHeight = 0;
    mMaxJumpHeight = MAX_JUMP_HEIGHT;
    mXval = 0;
    mYval = 0;
    mDirect = RIGHT;
    mStatus = IDLE;
    mOnGround = false;
    mJumpScores = 0;
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

void PlayerObject::setRectangle()
{
    mBox.x = mRect.x + 11;
    mBox.y = mRect.y + 9;
    mBox.w = (30 - 11) * mScale;
    mBox.h = (43 - 9) * mScale;
}

void PlayerObject::renderClips(SDL_Rect &camera)
{
    SDL_Rect *currentClip = &mSpriteClips[mFrame];
    if (mInputAction.jump)
    {
        // thay đổi hình ảnh nhảy nhân vật theo độ cao mMaxJumpheight
        if (mJumpHeight < mMaxJumpHeight - SPEED_JUMP * 6)
            mFrame = 0;
        else if (mJumpHeight >= mMaxJumpHeight - SPEED_JUMP * 6 && mJumpHeight < mMaxJumpHeight + SPEED_JUMP * 2)
            mFrame = 1;
        else
            mFrame = 2;
    }
    else
    {
        ++mFrame;
        if (mFrame == mNumberFrame)
            mFrame = 0;
    }

    // hướng quay trái, phải của nhân vật
    if (mDirect == LEFT)
        render(mRect.x - camera.x, mRect.y - camera.y, currentClip, 0, 0, SDL_FLIP_HORIZONTAL);
    else
        render(mRect.x - camera.x, mRect.y - camera.y, currentClip);
}

// hàm trả về trạng thái va chạm với map
// indexReturn, i_tile_return trả về vị trí va chạm để sau xử lý thay đổi map 
StatusCollisionwithMap PlayerObject::checkCollisonwithMap(vector<Tile *> &gTileSet, SDL_Rect &camera, int &indexReturn, int &i_tile_return)
{
    // khi nhân vật đang nhảy lên sẽ không va chạm
    if (mJumpHeight <= mMaxJumpHeight)
        return NONE;

    StatusCollisionwithMap statusCollision = NONE;
    bool collision = false;

    // lấy khung hình chữ nhật Box của nhân vật (vị trí, chiều cao, chiều rộng)
    SDL_Rect a = mBox;

    // check down
    // kiểm tra va chạm ở chân nhân vật khi di chuyển mYval
    a.x = mBox.x;
    a.y = mBox.y + mYval;

    // vị trí hàng i mà chân nhân vật đang ở 
    int i_tile = (a.y + a.h) / TILE_HEIGHT;

    // hàng i quá số lượng hàng của MAP thì die
    if (i_tile >= NUM_TILE_ROWS)
        return DIE;

    int j_tile = a.x / TILE_WIDTH + 1;
    if (j_tile < 0)
        j_tile = 0;

    // chỉ kiểm tra va chạm map khi nhân vật trong khung hình camera 
    if (checkCollision(mBox, camera))
    {
        // đổi từ mảng 2 chiều sang 1 chiều
        int index = i_tile * NUM_TILE_COLS + j_tile;

        for (int nextIndex = 0; nextIndex < 3; ++nextIndex)
        {
            if ((index + nextIndex) / NUM_TILE_COLS > i_tile + 1)
                break;
            if (gTileSet[index + nextIndex]->getType() != -1)
            {
                collision = (collision | checkCollision(a, gTileSet[index + nextIndex]->getBox()));
                if (collision)
                {
                    indexReturn = index + nextIndex;
                    i_tile_return = i_tile;

                    int typeTile = gTileSet[index + nextIndex]->getType();

                    if (typeTile == TILE_SPECIAL_BOX)
                    {
                        statusCollision = TAKE_SPECIAL_BOX;
                    }
                    else if (TILE_THORN_BEGIN <= typeTile && typeTile <= TILE_THORN_END)
                    {
                        statusCollision = DIE;
                    }
                    else if (TILE_CLOUD_BEGIN <= typeTile && typeTile <= TILE_CLOUD_END)
                    {
                        statusCollision = NONE;
                        i_tile_return = -1;
                    }
                    else
                    {
                        statusCollision = ON_GROUND;
                    }

                    break;
                }
            }
        }
    }

    return statusCollision;
}

void PlayerObject::doPlayer(vector<Tile *> &gTileSet, SDL_Rect &camera, int &indexReturn, int &i_tile_return, int &gScores)
{

    if (mInputAction.moveLeft)
        mXval = -SPEED_MOVE;
    if (mInputAction.moveRight)
        mXval = +SPEED_MOVE;
    if (!mInputAction.moveLeft && !mInputAction.moveRight)
        mXval = 0;

    if (mInputAction.jump)
    {
        if (mJumpHeight < mMaxJumpHeight)
        {
            if (mMaxJumpHeight == SPECIAL_MAX_JUMP_HEIGHT)
            {
                mJumpHeight += SPECIAL_SPEED_JUMP;
                mYval = -SPECIAL_SPEED_JUMP;
            }
            else
            {
                mJumpHeight += SPEED_JUMP;
                mYval = -SPEED_JUMP;
            }
        }
        else
        {
            if (mJumpHeight >= mMaxJumpHeight + SPEED_JUMP * 2)
                mMaxJumpHeight = MAX_JUMP_HEIGHT;
            mJumpHeight += SPEED_JUMP;
            mYval = +SPEED_JUMP;
        }
    }

    StatusCollisionwithMap stCollision = checkCollisonwithMap(gTileSet, camera, indexReturn, i_tile_return);

    setScores(gScores);

    if (stCollision == DIE)
    {
        mStatus = DEATH;
        Mix_PlayChannel(-1, gSDie, 0);
    }

    else
    {
        // khi nhân vật nhảy được lên mặt đất
        if (stCollision == ON_GROUND)
        {
            // chỉnh lại giá trị mYval để cho nhân vật đứng trên mặt đất sau khi di chuyển
            mYval = mYval - (mBox.y + mYval + mBox.h - gTileSet[indexReturn]->getBox().y) - 1;
            mJumpHeight = 0;
            gScores -= mYval;

            // âm thanh nhảy
            Mix_PlayChannel(-1, gSJump, 0);
        }
        else if (stCollision == TAKE_SPECIAL_BOX)
        {
            mJumpHeight = 0;
            mMaxJumpHeight = SPECIAL_MAX_JUMP_HEIGHT;
            
            // âm thanh nhặt hộp bí mật
            Mix_PlayChannel(-1, gSTakeBox, 0);
        }
    }
}

// di chuyển nhân vật
void PlayerObject::handleMove()
{
    mRect.x += mXval;
    mRect.y += mYval;

    mJumpScores -= mYval;

    if (mRect.x > SCREEN_WIDTH)
        mRect.x = 0 - mWidth / mNumberFrame;
    else if (mRect.x < 0 - mWidth / mNumberFrame)
        mRect.x = SCREEN_WIDTH;

    setRectangle();
}

void PlayerObject::handleInputAction(SDL_Event event)
{
    // nextStatus để kiểm tra có thay đổi trạng nhân vật hay không
    StatusPlayer nextStatus = mStatus;

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            mInputAction.moveLeft = true;
            mInputAction.moveRight = false;
            mDirect = LEFT;
            if (mStatus != JUMP)
                nextStatus = MOVE;
            break;
        case SDLK_d:
            mInputAction.moveRight = true;
            mInputAction.moveLeft = false;
            mDirect = RIGHT;
            if (mStatus != JUMP)
                nextStatus = MOVE;
            break;
        case SDLK_SPACE:
            mInputAction.jump = true;
            nextStatus = JUMP;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            mInputAction.moveLeft = false;
            break;
        case SDLK_d:
            mInputAction.moveRight = false;
            break;
        default:
            break;
        }
    }

    // nếu thay đổi trạng thái thì load lại ảnh theo trạng thái đó
    // sau khi space thì nhân  vật sẽ luôn trong trạng thái nhảy
    if (nextStatus != mStatus)
    {
        mStatus = nextStatus;
        mFrame = 0;
        if (mInputAction.jump || mInputAction.moveLeft || mInputAction.moveRight)
        {
            if (mInputAction.jump)
            {
                loadFromFile("Image/Player/3_player_jump_48x48.png");
                setNumFrame(NUM_FRAMES_JUMP);
                setClip();
                Mix_PlayChannel(-1, gSJump, 0);
            }
            else if ((mInputAction.moveLeft || mInputAction.moveRight) && mInputAction.jump == false)
            {
                loadFromFile("Image/Player/8_PlayerWalk_48x48.png");
                setNumFrame(NUM_FRAMES_MOVE);
                setClip();
            }
        }
    }

    if (!mInputAction.jump && !mInputAction.moveLeft && !mInputAction.moveRight && mStatus != IDLE)
    {
        mStatus = IDLE;
        mFrame = 0;
        loadFromFile("Image/Player/10_Character_Idle_48x48.png");
        setNumFrame(NUM_FRAMES_IDLE);
        setClip();
    }
}

void PlayerObject::setCamera(SDL_Rect &camera)
{
    // Center the camera over the dot
    camera.x = (mRect.x + mWidth * mScale / 2) - SCREEN_WIDTH / 2;
    camera.y = (mRect.y + mHeight * mScale / 2) - SCREEN_HEIGHT / 2;

    // Keep the camera in bounds
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > MAP_WIDTH - camera.w)
    {
        camera.x = MAP_WIDTH - camera.w;
    }
    if (camera.y > MAP_HEIGHT - camera.h)
    {
        camera.y = MAP_HEIGHT - camera.h;
    }
}

void PlayerObject::setScores(int &gScores)
{
    gScores += mJumpScores;
    mJumpScores = 0;
}

void PlayerObject::reset()
{
    mFrame = 0;
    mInputAction.moveRight = false;
    mInputAction.moveLeft = false;
    mInputAction.jump = false;
    mJumpHeight = 0;
    mMaxJumpHeight = MAX_JUMP_HEIGHT;
    mXval = 0;
    mYval = 0;
    mDirect = RIGHT;
    mStatus = IDLE;
    mOnGround = false;
    mJumpScores = 0;
}

void PlayerObject::loadSound()
{
    // Load sound effects
    gSJump = Mix_LoadWAV("sound/Jump.wav");
    gSTakeBox = Mix_LoadWAV("sound/take_special_box.wav");
    gSDie = Mix_LoadWAV("sound/die.wav");
}

void PlayerObject::freeSound()
{
    Mix_FreeChunk(gSJump);
    Mix_FreeChunk(gSTakeBox);
    Mix_FreeChunk(gSDie);
    gSJump = NULL;
    gSTakeBox = NULL;
    gSDie = NULL;
}