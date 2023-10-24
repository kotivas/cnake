#include "snake.h"
#include "config.h"
// TODO: убрать подключение конфига отсюда

Snake::Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
             SDL_Texture* tailTexure,float x, float y, float speed)
: m_pHead(nullptr), m_pTail(nullptr), m_score(0), m_segments(2),
m_bodyTexture(nullptr), m_headTexture(nullptr), m_tailTexture(nullptr)
{


    m_headTexture = headTexture;
    m_bodyTexture = bodyTexture;
    m_tailTexture = tailTexure;

    for (int i = 0; i < m_segments; i++){
        addSegment( { x, y} );
    } 
    
    m_speed = speed;

}

void Snake::updatePosition(){

    // FIXME: передвижение только на той который сейчас, а не на следующей

    for (SnakeSegment* pIter = m_pHead; pIter != nullptr; pIter = pIter->pNext){

        // MOVE 
        pIter->position.x += m_speed * pIter->direction.x; 
        pIter->position.y += m_speed * pIter->direction.y;   

        if ( int( pIter->position.x ) % GRID_SIZE == 0 && int( pIter->position.y ) % GRID_SIZE == 0){
            if ( pIter->pNext != nullptr ){
                pIter->pNext->buffdirection = pIter->direction;
            }
            pIter->direction = pIter->buffdirection;
            pIter->angle = pIter->direction.getAngle();
        }

        // maybe move this to the another func
        if ( pIter == m_pTail ){
            pIter->texture = m_tailTexture;
        } else if ( pIter == m_pHead ){
            pIter->texture = m_headTexture;
        } else if ( pIter != nullptr ){
            pIter->texture = m_bodyTexture;
        }
    }
}


void Snake::addScore(){
    // add new segment from the end
    addSegment( m_pTail->position );
    m_score++;
}

int Snake::getScore() const{
    return m_score;
}

// add new segment
void Snake::addSegment(Vector2f position){ 

    SnakeSegment* pNewSegment = new SnakeSegment();
    //
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

void Snake::setDirection(Vector2f direction){
    if ( m_pHead->direction.y != (direction.y * -1) || m_pHead->direction.x != (direction.x * -1) ){
        m_pHead->buffdirection = direction;
    }
}

// FIXME: убрать??
void Snake::setPosition(int x, int y){
    m_pHead->direction.x = x;
    m_pHead->direction.y = y;
}

// delete segment from beginning
void Snake::removeSegment(){
    if (m_pHead != nullptr){
        SnakeSegment* pRemove = m_pHead;
        m_pHead = m_pHead->pNext;

        SDL_DestroyTexture(pRemove->texture);
        delete pRemove;
    }
}

// get position
Vector2f Snake::getPosition() const{
    return m_pHead->position;
}

// get pointer to the object of head
SnakeSegment* Snake::getHead(){
    return m_pHead;
}

Snake::~Snake(){
    while ( m_pHead != nullptr ){   
        removeSegment();
    }
}

