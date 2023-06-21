#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "Constant.h"
#include "BaseObject.h"
#include "Tile.h"

// sound
extern Mix_Chunk *gSJump;
extern Mix_Chunk *gSTakeBox;
extern Mix_Chunk *gSDie;

enum Direction
{
	LEFT,
	RIGHT,
};

enum StatusPlayer
{
	JUMP,
	MOVE,
	IDLE,
	DEATH,
};

struct InputAction
{
	bool jump;
	bool moveRight;
	bool moveLeft;
};

enum StatusCollisionwithMap
{
	DIE,
	TAKE_SPECIAL_BOX,
	ON_GROUND,
	NONE,
};

class PlayerObject : public BaseObject
{
public:
	PlayerObject();
	~PlayerObject();

	void setXY(const int x, const int y);
	void setClip();
	void setNumFrame(const int val) { mNumberFrame = val; }
	void setRectangle();
	// Centers the camera over the dot
	void setCamera(SDL_Rect &camera);
	void setScores(int &gScores);

	void renderClips(SDL_Rect &camera);

	StatusCollisionwithMap checkCollisonwithMap(vector<Tile *> &gTileSet, SDL_Rect &camera, int &indexReturn, int &i_tile_return);

	void doPlayer(vector<Tile *> &gTileSet, SDL_Rect &camera, int &indexReturn, int &i_tile_return, int &gScores);
	void handleMove();
	void handleInputAction(SDL_Event event);

	SDL_Rect getRect() const { return mRect; }
	float getScale() const { return mScale; }
	StatusPlayer getStatus() { return mStatus; }
	SDL_Rect getBox() const { return mBox; }

	void reset();
	void loadSound();
	void freeSound();

private:
	SDL_Rect mRect;
	int mFrame;
	SDL_Rect mSpriteClips[20];
	int mNumberFrame;
	InputAction mInputAction;
	int mJumpHeight;
	int mMaxJumpHeight;
	int mXval;
	int mYval;
	Direction mDirect;
	StatusPlayer mStatus;
	bool mOnGround;
	SDL_Rect mBox;
	int mJumpScores;
};

#endif