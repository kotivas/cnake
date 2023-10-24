#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"
#include "snakesegment.h"

class Snake {
private:
    SnakeSegment*       m_pHead;
    SnakeSegment*       m_pTail;

    SDL_Texture*        m_bodyTexture;
    SDL_Texture*        m_headTexture;
    SDL_Texture*        m_tailTexture;

    float           m_speed; // pixels per frame
    int             m_segments;
    int             m_score;

    void            addSegment(Vector2f position);
    void            removeSegment();    

public:    
    Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
          SDL_Texture* tailTexure,float x, float y, float speed);

    void            setPosition(int x, int y);
    void            updatePosition();
    void            setDirection(Vector2f direction);

    Vector2f        getPosition() const;
    SnakeSegment*   getHead();

    void            addScore();
    int             getScore() const;

    ~Snake();
};