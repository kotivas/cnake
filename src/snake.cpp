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
        addSegment(i);
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

    // if ( int( m_pHead->position.x ) % 48 == 0 && int( m_pHead->position.y ) % 48 == 0 &&
    //         ( m_pHead->direction.x != m_pHead->buffdirection.x || m_pHead->direction.y != m_pHead->buffdirection.y) ){
        
    //     m_pHead->direction = m_pHead->buffdirection;

    //     // m_pHead->pNext->buffdirection = m_pHead->direction;
    //     // m_pHead->pNext->buffposition = m_pHead->position;
    // }

    for (SnakeSegment* pIter = m_pHead; pIter->pNext != nullptr; pIter = pIter->pNext){

        if ( int( pIter->position.x ) % 48 == 0 && int( pIter->position.y ) % 48 == 0 &&
            ( pIter->direction.x != pIter->buffdirection.x || pIter->direction.y != pIter->buffdirection.y) ){

            pIter->direction = pIter->buffdirection;

            pIter->pNext->buffdirection = pIter->direction;
            pIter->pNext->buffposition = pIter->position;
        }

        if ( pIter->pNext->position.x == pIter->pNext->buffposition.x && pIter->pNext->position.y == pIter->pNext->buffposition.y ){
            pIter->pNext->direction = pIter->pNext->buffdirection;
            pIter->pNext->buffposition = {0, 0};
        }

        pIter->pNext->position.x += m_speed * pIter->pNext->direction.x; 
        pIter->pNext->position.y += m_speed * pIter->pNext->direction.y;
    }
}
void Snake::addSegment(int index){

    SnakeSegment* pNewSegment = new SnakeSegment();

    if (m_pHead == nullptr){
        m_pTail = pNewSegment;
        m_pHead = pNewSegment;
    } else {
        m_pTail->pNext = pNewSegment;
        m_pTail = m_pTail->pNext;
    }
    pNewSegment->texture = m_bodyTexture;

    pNewSegment->position.x = 480;
    pNewSegment->position.y = 144 - (48 * index );
}


void Snake::updateHitbox(){
    m_pHead->hitbox = { m_pHead->position.x, m_pHead->position.y, m_pHead->hitbox.width, m_pHead->hitbox.lenght };
}

void Snake::setDirection(Vector2f direction){

    if ( m_pHead->direction.y != (direction.y * -1) || m_pHead->direction.x != (direction.x * -1) ){
        m_pHead->buffdirection = direction;
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