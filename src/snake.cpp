#include "snake.hpp"

Snake::Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
             SDL_Texture* tailTexure, SDL_Texture* angledTexture,
             float x, float y, float speed,
             Vector2f direction, int segments)
: m_pHead(nullptr), m_pTail(nullptr), m_bodyTexture(bodyTexture), m_angledTexture(angledTexture),
 m_headTexture(headTexture), m_tailTexture(tailTexure), m_speed(speed),
 m_initSegments(segments), m_initPosition{x, y}, m_initDirection{direction}
{   
    for (int i = 0; i < m_initSegments; i++){
        addSegment( m_initPosition, m_initDirection );
    } 

    m_pHead->buffdirection = m_initDirection; // initial direction of the snake

    m_pHead->direction = m_initDirection;

    m_score = 0;

}

void Snake::updatePosition( int grid_size ){ // FIXME: I'M GONNA KILL MY SELF 💀💀💀

    // if ( m_pHead->direction != m_pHead->buffdirection ){
    //     m_pHead->direction.x += 0.2 * m_pHead->buffdirection.x;
    //     m_pHead->direction.y += 0.2 * m_pHead->buffdirection.y;                 
    // }
    // m_pHead->direction.normalize();

    // m_pHead->angle = m_pHead->direction.getAngle();

    // m_pHead->position.x += m_speed * m_pHead->direction.x; 
    // m_pHead->position.y += m_speed * m_pHead->direction.y;   

    for (SnakeSegment* pIter = m_pHead; pIter != nullptr; pIter = pIter->pNext){

        pIter->position.x += m_speed * pIter->direction.x; 
        pIter->position.y += m_speed * pIter->direction.y;   

        if ( int( pIter->position.x ) % grid_size == 0 && int( pIter->position.y ) % grid_size == 0){
            if ( pIter->pNext != nullptr ){
                pIter->pNext->buffdirection = pIter->direction;
            }
            pIter->direction = pIter->buffdirection;
        }
    }

    updateTextures();
}

void Snake::updateTextures(){
    for (SnakeSegment* pIter = m_pHead; pIter != nullptr; pIter = pIter->pNext){
        if ( pIter == m_pHead ){
            pIter->texture = m_headTexture;
        } else if ( pIter == m_pTail ){
            pIter->texture = m_tailTexture;
        } else if ( pIter != nullptr ){
            pIter->texture = m_bodyTexture;
        }
        pIter->angle = pIter->direction.getAngle();
    }
}

// reset snake position and lenght
void Snake::reset(){

    while ( m_pHead != nullptr ){   
        removeSegment();
    }

    for (int i = 0; i < m_initSegments; i++){
        addSegment( m_initPosition, m_initDirection );
    }

    m_pHead->buffdirection = m_initDirection;
    m_pHead->direction  = m_initDirection;

    m_score = 0; // reset the score
}

void Snake::addScore(){
    // add new segment from the end
    addSegment( m_pTail->position, m_pTail->direction);
    m_score++;
}

// get formatted score string
std::string Snake::getScore() const{
    if ( m_score == 0 ){
        return "000";
    } else if (  m_score <= 9 ){
        return "00" + std::to_string(  m_score );
    } else if ( m_score <= 99 ){ 
        return "0" + std::to_string( m_score );
    } else {
        return std::to_string( m_score );
    }
}

// add new segment
void Snake::addSegment(Vector2f position, Vector2f direction){ 

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

void Snake::setDirection(float x, float y){
    if ( m_pHead->direction.y != (y * -1) || m_pHead->direction.x != (x * -1) ){
        m_pHead->buffdirection = {x, y};
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

// destructor
Snake::~Snake(){
    while ( m_pHead != nullptr ){   
        removeSegment();
    }

    SDL_DestroyTexture( m_headTexture );
    SDL_DestroyTexture( m_bodyTexture );
    SDL_DestroyTexture( m_tailTexture );
    SDL_DestroyTexture( m_angledTexture );
}

