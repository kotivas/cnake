#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"
#include "snakesegment.h"

#include "config.h"

#include <iostream>

class Snake {
private:
    SnakeSegment*   m_pHead;
    SnakeSegment*   m_pTail;

    SDL_Texture*    m_bodyTexture;
    SDL_Texture*    m_headTexture;
    SDL_Texture*    m_tailTexture;
    SDL_Texture*    m_angledTexture;    

    float           m_speed; // pixels per frame

    Uint8           m_score; // max 255

    int             m_initSegments;
    Vector2f        m_initPosition;
    Vector2f        m_initDirection;

    void            addSegment(Vector2f position, Vector2f direction);
    void            removeSegment();
    void            updateTextures();    

public:    
    Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
          SDL_Texture* tailTexure, SDL_Texture* angledTexture,
          float x, float y, float speed);

    void            updatePosition();
    void            setDirection(float x, float y);

    Vector2f        getPosition() const;
    SnakeSegment*   getHead();

    void            addScore();
    std::string     getScore() const;
 
    void            reset();

    ~Snake();
};