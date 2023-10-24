#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"

class Apple {
private:
    SDL_Texture*    m_texture;
    Vector2f        m_position;
public:
    Apple(SDL_Texture* texture, float x, float y);
    
    void            setPosition(int x, int y);
    Vector2f        getPosition() const;
    SDL_Texture*    getTexture() const;

    ~Apple();
};