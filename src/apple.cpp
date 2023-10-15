
#include "apple.h"

#include "config.h"

Apple::Apple(Screen* screen)
: m_texture( nullptr ), m_pos{GRID_SIZE*5, GRID_SIZE*6}
{
    m_texture = screen->loadTexture("./assets/apple.png");

    if ( m_texture == nullptr ){
        std::cout << SDL_GetError() << std::endl;
    }

}

Apple::~Apple(){
    SDL_DestroyTexture( m_texture );

    m_texture = nullptr;
}

Vector2 Apple::getPos() const{
    return m_pos;
}

void Apple::setPos(int x, int y){
    m_pos.x = x;
    m_pos.y = y;
}

SDL_Texture* Apple::getTexture() const{
    return m_texture;
}