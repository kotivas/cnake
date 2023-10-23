#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "screen.h"
#include "vector2f.h"
#include "hitbox.h"

#include "snakesegment.h"

class Snake {
private:
    SnakeSegment*       m_pHead;
    SnakeSegment*       m_pTail;

    SDL_Texture*        m_bodyTexture;
    SDL_Texture*        m_headTexture;
    SDL_Texture*        m_tailTexture;

    float           m_speed; // pixels per frame
    int             m_score;
    int             m_segments;

public:    
    Snake(Screen* screen, float x, float y, float width, float lenght, float speed);

    void            setPos(int x, int y);
    void            updatePosition();
    void            updateHitbox();
    void            setDirection(Vector2f direction);

    void            addSegment(Vector2f position);
    void            removeSegment();

    //Vector2f        getPos() const;
    //float           getAngle() const;
    //Vector2f        getDirection() const;

    Hitbox          getHitbox();

    SnakeSegment*   getHead();

    ~Snake();
};