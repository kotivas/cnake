#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"
#include "snakesegment.h"

#include <iostream>

class Snake {
private:
    SnakeSegment*       m_pHead;
    SnakeSegment*       m_pTail;

    SDL_Texture*        m_bodyTexture;
    SDL_Texture*        m_headTexture;
    SDL_Texture*        m_tailTexture;

    float           m_speed; // pixels per frame

    int             m_score;

    int             m_initSegments;
    Vector2f        m_initPosition;
    Vector2f        m_initDirection;

    void            addSegment(Vector2f position);
    void            removeSegment();
    void            updateTextures();    

public:    
    Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
          SDL_Texture* tailTexure, float x, float y, float speed,
          Vector2f direction, int segments);

    void            updatePosition( const short GRID_SIZE );
    void            setDirection(Vector2f direction);

    Vector2f        getPosition() const;
    SnakeSegment*   getHead();

    void            addScore();
    std::string             getScore() const;
 
    void reset();

    ~Snake();
};