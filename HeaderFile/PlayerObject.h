#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "Constant.h"
#include "BaseObject.h"

enum StatusPlayer
{
	JUMP,
	DIE,
	IDLE,
	WALK,
};

enum Directions
{
	LEFT = -1,
	RIGHT = 1,
};

struct InputAction
{
	bool jump;
	bool walk;
};


class PlayerObject : public BaseObject
{
public:
	PlayerObject();
	~PlayerObject();

	void setXY(const int x, const int y);
	void setClip();
	void setNumFrame(const int val) { mNumberFrame = val; }

	void renderClips(const int x, const int y);

	void handleMove();
	void handleInputAction(SDL_Event event);

	SDL_Rect getRect() const { return mRect; }

private:
	SDL_Rect mRect;
	int mFrame;
	SDL_Rect mSpriteClips[20];
	int mNumberFrame;
	StatusPlayer mStatus;
	Directions mDirect;
	InputAction mInputAction;
};

#endif