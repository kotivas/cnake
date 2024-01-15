#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"
#include "snakesegment.h"

#include "config.h"

#include <list>

class Snake {
private:
    SDL_Texture*    _bodyTexture;
    SDL_Texture*    _headTexture;
    SDL_Texture*    _tailTexture;

    // measured in pixels per second
    float           _speed;

    int             _initSegments;
    Vector2f        _initPosition;
    Vector2f        _initDirection;

    void            addSegment(Vector2f position, Vector2f direction);
    void            removeSegment();
    void            updateTextures();   

    std::list<SnakeSegment*> _segments; 

public:    
    Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture, SDL_Texture* tailTexure);

    void            step();
    void            setDirection(float x, float y);

    Vector2f        getPosition() const;
    std::list<SnakeSegment*>   getSegments();
    SnakeSegment*   getHead();

    void            addScore();
 
    void            reset();

    ~Snake();
};