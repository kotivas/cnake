#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"
#include "snakesegment.h"

#include "config.h"

#include <list>
#include <iostream>

class Snake {
private:
    SDL_Texture*    m_bodyTexture;
    SDL_Texture*    m_headTexture;
    SDL_Texture*    m_tailTexture;

    float           m_speed; // pixels per frame

    int             m_initSegments;
    Vector2f        m_initPosition;
    Vector2f        m_initDirection;

    void            addSegment(Vector2f position, Vector2f direction);
    void            removeSegment();
    void            updateTextures();   

    std::list<SnakeSegment*> m_segments; 

public:    
    Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
          SDL_Texture* tailTexure, float x, float y, float speed);

    void            updatePosition();
    void            setDirection(float x, float y);

    Vector2f        getPosition() const;
    std::list<SnakeSegment*>   getSegments();
    SnakeSegment*   getHead();

    void            addScore();
 
    void            reset();

    ~Snake();
};