#include "apple.h"

Apple::Apple(SDL_Texture* texture, float x, float y)
: m_texture( texture ), m_position{x, y}
{}

Vector2f Apple::getPosition() const{
    return m_position;
}

void Apple::setPosition(int x, int y){
    m_position.x = x;
    m_position.y = y;
}

SDL_Texture* Apple::getTexture() const{
    return m_texture;
}

Apple::~Apple(){
    SDL_DestroyTexture( m_texture );
    m_texture = nullptr;
}
