#pragma once
#include <SDL.h>
#include "vector2f.h"

struct Apple{

    Apple(SDL_Texture* textur, float x, float y)
    : texture(textur), position(x, y), initPosition(x ,y)
    {}

    SDL_Texture*    texture;
    Vector2f        position;
    Vector2f        initPosition;
};
