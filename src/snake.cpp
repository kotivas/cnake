#include "snake.hpp"

Snake::Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture,
             SDL_Texture* tailTexure, float x, float y, float speed)
: m_bodyTexture(bodyTexture), m_headTexture(headTexture),
 m_tailTexture(tailTexure), m_speed(speed), m_initPosition{x, y}
{   
    m_initSegments = 4*2;
    m_initDirection = {1, 0};

    reset();
}

// update snake position 
void Snake::updatePosition(){
    // MOST BADASS FUNCTION IN THE ENTIRE GAME
    for (auto iter = m_segments.begin(); iter != m_segments.end(); iter++){

        SnakeSegment* segment = *iter;

        segment->position.x += m_speed * segment->direction.x; 
        segment->position.y += m_speed * segment->direction.y;   

        if ( int( segment->position.x ) % SEGMENT_INDENT == 0 && int( segment->position.y ) % SEGMENT_INDENT == 0){
            if ( segment != m_segments.back() ){
                (*std::next(iter))->buffdirection = segment->direction;
            }
        }
        if ( int( segment->position.x ) % BLOCK_SIZE == 0 && int( segment->position.y ) % BLOCK_SIZE == 0){
            segment->direction = segment->buffdirection;
        }
    }
    updateTextures();
}

// update textures for all snake segments
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
       addSegment( {m_initPosition.x - (SEGMENT_INDENT * i), m_initPosition.y}, m_initDirection);
    } 

    m_segments.front()->buffdirection = m_initDirection;
    m_segments.front()->direction  = m_initDirection;
}

void Snake::addScore(){ // FIXME   REMOVE?
    // add new segment from the end
    for (int i = 0; i < 4; i++){
        addSegment( m_segments.back()->position, m_segments.back()->direction);
    }
}

// add new segment
void Snake::addSegment(Vector2f position, Vector2f direction){ 

    // memory allocate for new segment
    SnakeSegment* pNewSegment = new SnakeSegment();

    // calculating the indent from the last segment
    position.x += SEGMENT_INDENT * -direction.x;
    position.y += SEGMENT_INDENT * -direction.y;

    pNewSegment->position = position;
    pNewSegment->direction = direction;

    pNewSegment->texture = m_tailTexture;
    pNewSegment->angle = direction.getAngle();

    m_segments.push_back(pNewSegment);
}

void Snake::setDirection(float x, float y){
    m_segments.front()->buffdirection = {x, y};
}

// deleting a front segment
void Snake::removeSegment(){
    delete m_segments.front();
    m_segments.pop_front();
}

// get head position
Vector2f Snake::getPosition() const{
    return m_segments.front()->position;
}

// get list of the snake segments
std::list<SnakeSegment*> Snake::getSegments(){
    return m_segments;
}

// get pointer to the object of head
SnakeSegment* Snake::getHead(){
    return m_segments.front();
}

// destructor
Snake::~Snake(){
    m_segments.clear(); 
}

