#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2f.h"
#include "screen.h"
#include "hitbox.h"

class Apple {
private:
    SDL_Texture*    m_texture;
    Vector2f        m_position;
    Hitbox          m_hitbox;
public:
    Apple(Screen* screen, float x, float y, float width, float lenght);
    
    void            setPosition(int x, int y);
    Vector2f        getPosition() const;

    SDL_Texture*    getTexture() const;

    void            updateHitbox();    
    Hitbox          getHitbox();

    ~Apple();
};