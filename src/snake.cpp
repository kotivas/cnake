/* Snake entity

*/

#include "snake.h"

#include <cmath> 

Snake::Snake(Screen* screen, float width, float lenght, float speed)
: m_head(nullptr), m_body(nullptr), m_tail(nullptr),
m_position{200, 400}, m_counterVector{0.0f, 0.0f},
m_direction{0.0f, -1.0f}, m_angle(0.0f)
{
    m_head = screen->loadTexture("./assets/head_up.png");

    if ( m_head == nullptr ){
        std::cout << SDL_GetError() << std::endl;
    }
    
    m_speed = speed;

    m_hitbox = {m_position.x, m_position.y, width, lenght};

}

void Snake::updatePosition(){

    m_counterVector = {0.0f, 0.0f};

    /*if ( sqrt( (m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) ) > m_speed ){
        m_counterVector.x = sqrt( (m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) ) - m_speed * m_speed;
        m_counterVector.y = sqrt( (m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) ) - m_speed * m_speed;
    }*/

    // std::cout << sqrt( (m_speed * m_speed) + (m_speed * m_speed) ) << std::endl;
    // std::cout << "x:";
    // std::cout << (m_speed * m_direction.x) - (m_counterVector.x * m_direction.x) << std::endl;
    // std::cout << "y:";
    // std::cout << (m_speed * m_direction.y) - (m_counterVector.y * m_direction.y) << std::endl;
    m_counterVector = m_direction;
    m_counterVector.normalize();
    
    m_position.x += m_speed * m_counterVector.x; // (m_speed * m_direction.x) - (m_counterVector.x * m_direction.x);
    m_position.y += m_speed * m_counterVector.y;//(m_speed * m_direction.y) - (m_counterVector.y * m_direction.y);
}

void Snake::updateHitbox(){
    m_hitbox = { m_position.x, m_position.y, m_hitbox.width, m_hitbox.lenght };
}

void Snake::setAngle(int angle){
    m_angle = angle;
}

void Snake::setDirection(int dirX, int dirY){

    if ( m_direction.x != (dirX * -1) ){
         m_direction.x = dirX;
    }
    if ( m_direction.y != (dirY * -1) ){
        m_direction.y = dirY;
    }
}

void Snake::setPos(int x, int y){
    //m_counterVector.x = sqrt( (m_direction.x * m_direction.x) + (m_direction.y * m_direction.y) );

    m_direction.x = x;
    m_direction.y = y;
}

Snake::~Snake(){
    SDL_DestroyTexture( m_head );
    SDL_DestroyTexture( m_body );
    SDL_DestroyTexture( m_tail );

    m_head = nullptr;
    m_body = nullptr;
    m_tail = nullptr;
}

// INLINE FUNCS

SDL_Texture* Snake::getTextureHead() const{
    return m_head;
}

Vector2f Snake::getPos() const{
    return m_position;
}

float Snake::getAngle() const{
    return m_angle;
}

Vector2f Snake::getDirection() const{
    return m_direction;
}

Hitbox Snake::getHitbox(){
    return m_hitbox;
}
