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

    //Vector2f        m_position;
    //Vector2f        m_direction;

    float           m_speed; // pixels per frame
    //Hitbox          m_hitbox;
    //float           m_angle;
    int             m_score;
    int             m_segments;

public:    
    Snake(Screen* screen, float x, float y, float width, float lenght, float speed);

    void            setPos(int x, int y);
    void            updatePosition();
    void            updateHitbox();
    void            setDirection(int dirX, int dirY);

    void            addSegment();
    void            removeSegment();

    SDL_Texture*    getTextureHead() const;
    Vector2f        getPos() const;
    float           getAngle() const;
    Vector2f        getDirection() const;
    int             getLenght() const;

    Hitbox          getHitbox();

    SnakeSegment*   getHead();
    

    ~Snake();
};