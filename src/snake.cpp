/* Snake entity
snake object
*/

#include "snake.h"

Snake::Snake(Screen* screen, float x, float y, float width, float lenght, float speed)
: m_pHead(nullptr), m_pTail(nullptr), m_bodyTexture(nullptr), m_score(0), m_segments(3)
{

    m_bodyTexture = screen->loadTexture("./assets/body_vertical.png");

    for (int i = 0; i < m_segments; i++)
    {
        addSegment();
    }

    m_pTail->texture = screen->loadTexture("./assets/tail_up.png");

    m_pHead->texture = screen->loadTexture("./assets/head_down.png");

    if ( m_pHead->texture == nullptr || m_bodyTexture == nullptr || m_pTail->texture == nullptr ){
        std::cout << "UNABLE TO SET TEXTURE" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }
    
    m_speed = speed;

    m_pHead->position = {x, y};

    m_pHead->hitbox = {m_pHead->position.x, m_pHead->position.y, width, lenght};

}

void Snake::updatePosition(){

    m_pHead->direction.normalize();
    
    m_pHead->position.x += m_speed * m_pHead->direction.x; 
    m_pHead->position.y += m_speed * m_pHead->direction.y;

    if ( int( m_pHead->position.x ) % 64 == 0 && int( m_pHead->position.y ) % 64 == 0 ){
        m_pHead->direction = m_pHead->buffdirection;
    }

    for (SnakeSegment* pIter = m_pHead; pIter->pNext != nullptr; pIter = pIter->pNext){

        // 💀💀💀
        
    }
}

void Snake::addSegment(){

    SnakeSegment* pNewSegment = new SnakeSegment();

    if (m_pHead == nullptr){
        m_pTail = pNewSegment;
        m_pHead = pNewSegment;
    } else {
        m_pTail->pNext = pNewSegment;
        m_pTail = m_pTail->pNext;
    }
    pNewSegment->texture = m_bodyTexture;

}


void Snake::updateHitbox(){
    m_pHead->hitbox = { m_pHead->position.x, m_pHead->position.y, m_pHead->hitbox.width, m_pHead->hitbox.lenght };
}

void Snake::setDirection(int dirX, int dirY){

    if ( m_pHead->direction.x != (dirX * -1) ){
         m_pHead->buffdirection.x = dirX;
    }
    if ( m_pHead->direction.y != (dirY * -1)  ){
        m_pHead->buffdirection.y = dirY;
    }

    m_pHead->angle = m_pHead->buffdirection.getAngle();

}

void Snake::setPos(int x, int y){
    m_pHead->direction.x = x;
    m_pHead->direction.y = y;
}

void Snake::removeSegment(){
    if (m_pHead != nullptr){
        SnakeSegment* pRemove = m_pHead;
        m_pHead = m_pHead->pNext;

        SDL_DestroyTexture(pRemove->texture);
        delete pRemove;
    }
}

Snake::~Snake(){
    while ( m_pHead != nullptr ){   
        removeSegment();
    }
}

// INLINE FUNCS

SDL_Texture* Snake::getTextureHead() const{
    return m_pHead->texture;
}

Vector2f Snake::getPos() const{
    return m_pHead->position;
}

float Snake::getAngle() const{
    return m_pHead->angle;
}

Vector2f Snake::getDirection() const{
    return m_pHead->direction;
}

Hitbox Snake::getHitbox(){
    return m_pHead->hitbox;
}

int Snake::getLenght() const{
    return m_segments;
}

SnakeSegment* Snake::getHead(){
    return m_pHead;
}