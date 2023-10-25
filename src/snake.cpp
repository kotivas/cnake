#include "snake.h"
#include "config.h"
// TODO: убрать подключение конфига отсюда

Snake::Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
             SDL_Texture* tailTexure, float x, float y, float speed,
             Vector2f direction, int segments)
: m_pHead(nullptr), m_pTail(nullptr), m_bodyTexture(bodyTexture),
 m_headTexture(headTexture), m_tailTexture(tailTexure), m_speed(speed),
 m_initSegments( segments ), m_initPosition{ x, y }, m_initDirection{ direction }
{   
    for (int i = 0; i < m_initSegments; i++){
        addSegment( { m_initPosition.x, m_initPosition.y } );
    } 

    m_pHead->buffdirection = m_initDirection; // initial direction of the snake

}

void Snake::updatePosition(){

    // FIXME: передвижение только на той который сейчас, а не на следующей
    // FIXME: пофиксить спавн

    for (SnakeSegment* pIter = m_pHead; pIter != nullptr; pIter = pIter->pNext){

        // MOVE 
        pIter->position.x += m_speed * pIter->direction.x; 
        pIter->position.y += m_speed * pIter->direction.y;   

        if ( int( pIter->position.x ) % GRID_SIZE == 0 && int( pIter->position.y ) % GRID_SIZE == 0){
            if ( pIter->pNext != nullptr ){
                pIter->pNext->buffdirection = pIter->direction;

            if ( m_pHead->position.x == pIter->position.x &&
                m_pHead->position.y == pIter->position.y &&
                m_pHead != pIter  ){
                reset();
                break;
            }
            }
            pIter->direction = pIter->buffdirection;
            pIter->angle = pIter->direction.getAngle();
        }

        updateTextures();
    }
}

void Snake::updateTextures(){
    for (SnakeSegment* pIter = m_pHead; pIter != nullptr; pIter = pIter->pNext){
        if ( pIter == m_pTail ){
            pIter->texture = m_tailTexture;
        } else if ( pIter == m_pHead ){
            pIter->texture = m_headTexture;
        } else if ( pIter != nullptr ){
            pIter->texture = m_bodyTexture;
        }        
    }
}

void Snake::reset(){

    while ( m_pHead != nullptr ){   
        removeSegment();
    }

    for (int i = 0; i < m_initSegments; i++){
        addSegment( { m_initPosition.x, m_initPosition.y } );
    }

    m_pHead->buffdirection = m_initDirection;

    std::cout << "reseted" << std::endl;

}

void Snake::addScore(){
    // add new segment from the end
    addSegment( m_pTail->position );
}

// add new segment
void Snake::addSegment(Vector2f position){ 

    SnakeSegment* pNewSegment = new SnakeSegment();

    if (m_pHead == nullptr){
        m_pTail = pNewSegment;
        m_pHead = pNewSegment;
    } else {
        m_pTail->pNext = pNewSegment;
        m_pTail = m_pTail->pNext;
    }
    pNewSegment->texture = m_bodyTexture;
    pNewSegment->position = position;
}

void Snake::setDirection(Vector2f direction){
    if ( m_pHead->direction.y != (direction.y * -1) || m_pHead->direction.x != (direction.x * -1) ){
        m_pHead->buffdirection = direction;
    }
}

// delete segment from beginning
void Snake::removeSegment(){
    if (m_pHead != nullptr){
        SnakeSegment* pRemove = m_pHead;
        m_pHead = m_pHead->pNext;

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

    SDL_DestroyTexture( m_headTexture );
    SDL_DestroyTexture( m_bodyTexture );
    SDL_DestroyTexture( m_tailTexture );
}

