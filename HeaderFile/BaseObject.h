#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Constant.h"

class BaseObject
{
public:
    // Initializes variables
    BaseObject();

    // Deallocates memory
    ~BaseObject();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Deallocates texture
    void free();

    // Renders texture at given point
    virtual void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Gets image dimensions
    int getWidth();
    int getHeight();

    //Set Scale
    void setScale(const float val);

    //Get file name
    std::string getFilename() const { return mFileName; }

protected:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;

    float mScale;

    std::string mFileName;
};

#endif