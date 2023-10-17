#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2f.h"
#include "screen.h"
#include "hitbox.h"

class Apple {
private:
    SDL_Texture* m_texture;
    Vector2f m_position;

    Hitbox m_hitbox;
public:
    Apple(Screen* screen, float width, float lenght);
    ~Apple();

    Vector2f getPos() const;
    void setPos(int x, int y);

    void updateHitbox();

    SDL_Texture* getTexture() const;

    Hitbox getHitbox();

};