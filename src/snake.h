#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "screen.h"
#include "vector2.h"
#include "config.h"

class Snake {
private:
    SDL_Texture* m_head;
    SDL_Texture* m_body;
    SDL_Texture* m_tail;
    Vector2 m_pos;
    Vector2 m_currDirection;
    Vector2 m_nextDirection;

    int m_speed; // pixels per frame

    int m_angle;
public:
    Snake(Screen* screen);

    SDL_Texture* getTextureHead() const;

    Vector2 getPos() const;
    void setPos(int x, int y);

    int getAngle() const;
    void setAngle(int angle);

    void update();

    void setDirection(int dirX, int dirY);
    Vector2 getDirection() const;

    ~Snake();
};