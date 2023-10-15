#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2.h"
#include "screen.h"

class Apple {
private:
    SDL_Texture* m_texture;
    Vector2 m_pos;
public:
    Apple(Screen* screen);
    ~Apple();

    Vector2 getPos() const;
    void setPos(int x, int y);

    SDL_Texture* getTexture() const;

};