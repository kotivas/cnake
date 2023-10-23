/* Snake entity
snake object
*/

#include "snake.h"
#include "config.h"
// TODO: убрать подключение конфига отсюда

Snake::Snake(Screen* screen, float x, float y, float width, float lenght, float speed)
: m_pHead(nullptr), m_pTail(nullptr), m_score(0), m_segments(3),
m_bodyTexture(nullptr), m_headTexture(nullptr), m_tailTexture(nullptr)
{
    // FIXME: вынести загрузку текстур в main?
    m_bodyTexture = screen->loadTexture("./assets/body_vertical.png");
    m_tailTexture = screen->loadTexture("./assets/tail_up.png");
    m_headTexture = screen->loadTexture("./assets/head_down.png");

    if ( m_bodyTexture == nullptr || m_tailTexture == nullptr || m_headTexture == nullptr ){
        std::cout << "UNABLE TO LOAD TEXTURE: " << SDL_GetError() << std::endl;
    }

    for (int i = 0; i < m_segments; i++){
        addSegment( { x, y} );
    } 
    
    m_pHead->hitbox = {m_pHead->position.x, m_pHead->position.y, width, lenght};   
    m_speed = speed;

}

void Snake::updatePosition(){

    // FIXME: передвижение только на той который сейчас, а не на следующей

    m_pTail->texture = m_tailTexture;
    m_pHead->texture = m_headTexture;

    for (SnakeSegment* pIter = m_pHead; pIter != nullptr; pIter = pIter->pNext){

        /* MOVE */
        pIter->position.x += m_speed * pIter->direction.x; 
        pIter->position.y += m_speed * pIter->direction.y;   

        if ( int( pIter->position.x ) % GRID_SIZE == 0 && int( pIter->position.y ) % GRID_SIZE == 0){
            if ( pIter->pNext != nullptr ){
                pIter->pNext->buffdirection = pIter->direction;
            }
            pIter->direction = pIter->buffdirection;
            pIter->angle = pIter->direction.getAngle();
        }
    }
}

// FIXME: переименовать в spawn segment
void Snake::addSegment(Vector2f position){ 

    SnakeSegment* pNewSegment = new SnakeSegment();

    if (m_pHead == nullptr){
        m_pTail = pNewSegment;
        m_pHead = pNewSegment;
    } else {
        m_pTail->pNext = pNewSegment;
        m_pTail = m_pTail->pNext;
        pNewSegment->direction = m_pTail->direction;
    }
    pNewSegment->texture = m_bodyTexture;
    pNewSegment->position = position;
}


void Snake::updateHitbox(){
    m_pHead->hitbox = { m_pHead->position.x, m_pHead->position.y, m_pHead->hitbox.width, m_pHead->hitbox.lenght };
}

void Snake::setDirection(Vector2f direction){

    if ( m_pHead->direction.y != (direction.y * -1) || m_pHead->direction.x != (direction.x * -1) ){
        m_pHead->buffdirection = direction;
    }

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

// SDL_Texture* Snake::getTextureHead() const{
//     return m_pHead->texture;
// }

// Vector2f Snake::getPos() const{
//     return m_pHead->position;
// }

// float Snake::getAngle() const{
//     return m_pHead->angle;
// }

// Vector2f Snake::getDirection() const{
//     return m_pHead->direction;
// }

Hitbox Snake::getHitbox(){
    return m_pHead->hitbox;
}

SnakeSegment* Snake::getHead(){
    return m_pHead;
}