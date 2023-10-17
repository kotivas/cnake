/* Apple entity

*/

#include "apple.h"

#include "config.h"

Apple::Apple(Screen* screen, float width, float lenght)
: m_texture( nullptr ), m_position{10, 520}
{
    m_texture = screen->loadTexture("./assets/apple.png");

    if ( m_texture == nullptr ){
        std::cout << SDL_GetError() << std::endl;
    }

    m_hitbox = { m_position.x, m_position.y, width, lenght };

}

void Apple::updateHitbox(){
    m_hitbox = { m_position.x, m_position.y, m_hitbox.width, m_hitbox.lenght };
}

Apple::~Apple(){
    SDL_DestroyTexture( m_texture );

    m_texture = nullptr;
}

Vector2f Apple::getPos() const{
    return m_position;
}

void Apple::setPos(int x, int y){
    m_position.x = x;
    m_position.y = y;
}

SDL_Texture* Apple::getTexture() const{
    return m_texture;
}

Hitbox Apple::getHitbox(){
    return m_hitbox;
}