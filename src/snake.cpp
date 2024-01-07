#include "snake.hpp"

Snake::Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
             SDL_Texture* tailTexure, SDL_Texture* angledTexture,
             float x, float y, float speed)
: m_bodyTexture(bodyTexture),
 m_headTexture(headTexture), m_tailTexture(tailTexure),m_angledTexture(angledTexture),
 m_speed(speed), m_initPosition{x, y}
{   

    m_initSegments = 3;
    m_initDirection = {1, 0};

    for (int i = 0; i < m_initSegments; i++){
       addSegment( {m_initPosition.x - ( BLOCK_SIZE * i), m_initPosition.y}, m_initDirection);
    } 

    m_segments.front()->buffdirection = m_initDirection; // initial direction of the snake

    m_score = 0;

}

void Snake::updatePosition(){ // FIXME: I'M GONNA KILL MY SELF 💀💀💀

    for (auto iter = m_segments.begin(); iter != m_segments.end(); iter++){ // OPTIMIZE:-------------------------------

        SnakeSegment* segment = *iter;

        segment->position.x += m_speed * segment->direction.x; 
        segment->position.y += m_speed * segment->direction.y;   

        if ( int( segment->position.x ) % BLOCK_SIZE == 0 && int( segment->position.y ) % BLOCK_SIZE   == 0){
            if ( segment != m_segments.back() ){
                (*std::next(iter))->buffdirection = segment->direction;
            }
            segment->direction = segment->buffdirection;
        }
    }
    updateTextures();
}

void Snake::updateTextures(){

    for (auto segment : m_segments){
        if ( segment == m_segments.front() ){
            segment->texture = m_headTexture;
        } else if ( segment == m_segments.back() ){
            segment->texture = m_tailTexture;
        } else {
            segment->texture = m_bodyTexture;
        }
        segment->angle = segment->direction.getAngle();
    }
}

// reset snake position and lenght
void Snake::reset(){

    m_segments.clear();

    for (int i = 0; i < m_initSegments; i++){
       addSegment( {m_initPosition.x - (48 * i), m_initPosition.y}, m_initDirection);
    } 

    m_segments.front()->buffdirection = m_initDirection;
    m_segments.front()->direction  = m_initDirection;

    m_score = 0; // reset the score
}

void Snake::addScore(){
    // add new segment from the end
    addSegment( m_segments.back()->position, m_segments.back()->direction); // OPTIMIZE: remove arguments
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

    if (direction == Vector2f{1, 0}){
        position.x -= BLOCK_SIZE;
    } else if (direction == Vector2f{-1, 0}){
        position.x += BLOCK_SIZE;
    } else if (direction == Vector2f{0, 1}){
        position.y -= BLOCK_SIZE;
    } else if (direction == Vector2f{0, -1}){
        position.y += BLOCK_SIZE;
    }

    // if (m_pHead == nullptr){
    //     m_pTail = pNewSegment;
    //     m_pHead = pNewSegment;
    // } else {
    //     m_pTail->pNext = pNewSegment;
    //     m_pTail = m_pTail->pNext;
    // }
    pNewSegment->texture = m_bodyTexture;
    pNewSegment->position = position;

    pNewSegment->direction = direction;

    m_segments.push_back(pNewSegment);
    
}

void Snake::setDirection(float x, float y){
    m_segments.front()->buffdirection = {x, y};
}

// delete segment from beginning
void Snake::removeSegment(){
    // if (m_pHead != nullptr){
    //     SnakeSegment* pRemove = m_pHead;
    //     m_pHead = m_pHead->pNext;

    //     delete pRemove;
    // }
    delete m_segments.front();
    m_segments.pop_front();
}

// get position
Vector2f Snake::getPosition() const{
    return m_segments.front()->position;
}

// get pointer to the object of head
std::list<SnakeSegment*> Snake::getSegments(){
    return m_segments;
}

SnakeSegment* Snake::getHead(){
    return m_segments.front();
}

// destructor
Snake::~Snake(){
    m_segments.clear(); 

    SDL_DestroyTexture( m_headTexture );
    SDL_DestroyTexture( m_bodyTexture );
    SDL_DestroyTexture( m_tailTexture );
}

