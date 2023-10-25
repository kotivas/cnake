#include "apple.h"

Apple::Apple(SDL_Texture* texture, float x, float y)
: m_texture( texture ), m_initPosition{x, y}
{
    m_position = m_initPosition;
}

Vector2f Apple::getPosition() const{
    return m_position;
}

void Apple::setPosition(int x, int y){
    m_position.x = x;
    m_position.y = y;
}

void Apple::reset(){
    m_position = m_initPosition;
}

SDL_Texture* Apple::getTexture() const{
    return m_texture;
}

Apple::~Apple(){
    SDL_DestroyTexture( m_texture );
    m_texture = nullptr;
}
