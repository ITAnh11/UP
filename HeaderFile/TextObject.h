#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "Constant.h"
#include "BaseObject.h"

class TextObject :public BaseObject
{
public:
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	SDL_Rect getPos() const { return mBox; }

	void setPos(const int x, const int y);
private:
	SDL_Rect mBox;
};

#endif //!TEXT_OBJECT_H_