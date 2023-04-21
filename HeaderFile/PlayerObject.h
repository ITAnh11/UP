#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "Constant.h"
#include "BaseObject.h"

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
};

struct InputAction
{
	bool jump;
	bool moveRight;
	bool moveLeft;
};


class PlayerObject : public BaseObject
{
public:
	PlayerObject();
	~PlayerObject();

	void setXY(const int x, const int y);
	void setClip();
	void setNumFrame(const int val) { mNumberFrame = val; }

	void renderClips(SDL_Rect &camera);

	void doPlayer();
	void handleMove();
	void handleInputAction(SDL_Event event);

	SDL_Rect getRect() const { return mRect; }

	//Centers the camera over the dot
    void setCamera( SDL_Rect& camera );

private:
	SDL_Rect mRect;
	int mFrame;
	SDL_Rect mSpriteClips[20];
	int mNumberFrame;
	InputAction mInputAction;
	int mJumpHeight;
	int mXval;
	int mYval;
	Direction mDirect;
	StatusPlayer mStatus;
};

#endif