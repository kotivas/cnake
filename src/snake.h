#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "screen.h"
#include "vector2f.h"
#include "hitbox.h"

class Snake {
private:
    SDL_Texture* m_head;
    SDL_Texture* m_body;
    SDL_Texture* m_tail;    

    Vector2f m_position;
    Vector2f m_direction;
    Vector2f m_counterVector;

    float m_speed; // pixels per frame

    Hitbox m_hitbox;

    float m_angle;
public:    
    Snake(Screen* screen, float x, float y, float width, float lenght, float speed);

    void setPos(int x, int y);

    void updatePosition();
    void updateHitbox();

    void setDirection(int dirX, int dirY);

    SDL_Texture* getTextureHead() const;
    Vector2f getPos() const;
    float getAngle() const;
    Vector2f getDirection() const;

    Hitbox getHitbox();

    ~Snake();
};