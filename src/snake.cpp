#include "snake.hpp"

Snake::Snake(SDL_Texture* headTexture, SDL_Texture* bodyTexture, SDL_Texture* tailTexure)
: _bodyTexture(bodyTexture), _headTexture(headTexture),
 _tailTexture(tailTexure)
{   
    _segmentIndent = 4;
    _segmentsPerScore = 6;
    _speed = 4.f;

    _initSegments = _segmentsPerScore * 3;
    _initDirection = {1, 0};
    _initPosition = {288, 336};

    reset();

}

// update snake position 
void Snake::step(){
    // MOST BADASS FUNCTION IN THE ENTIRE GAME
    for (auto iter = _segments.begin(); iter != _segments.end(); iter++){

        SnakeSegment* segment = *iter;

        /* movement is NOT tied to frame time
        actually i tried to do it, but due to the inconsistent value of the pixels by which the snake moves,
        it simply skips the rotation due to the fact
        that the rotation algorithm is built on checking whether the position is completely divisible by the block size
        */
        segment->position.x += (_speed * segment->direction.x);
        segment->position.y += (_speed * segment->direction.y);

        if ( int( segment->position.x ) % _segmentIndent == 0 && int( segment->position.y ) % _segmentIndent == 0){
            if ( segment != _segments.back() ){
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

    for (auto segment : _segments){
        if ( segment == _segments.front() ){
            segment->texture = _headTexture;
        } else if ( segment == _segments.back() ){
            segment->texture = _tailTexture;
        } else {
            segment->texture = _bodyTexture;
        }
        segment->angle = segment->direction.getAngle();
    }
}

// reset snake position and lenght
void Snake::reset(){

    _segments.clear();

    for (int i = 0; i < _initSegments; i++){
       addSegment( {_initPosition.x - (_segmentIndent * i), _initPosition.y}, _initDirection);
    } 

    _segments.front()->buffdirection = _initDirection;
    _segments.front()->direction  = _initDirection;
}

void Snake::addScore(){ // FIXME   REMOVE?
    // add new segment from the end
    for (int i = 0; i < _segmentsPerScore; i++){
        addSegment( _segments.back()->position, _segments.back()->direction);
    }
}

// add new segment
void Snake::addSegment(Vector2f position, Vector2f direction){ 

    // memory allocate for new segment
    SnakeSegment* pNewSegment = new SnakeSegment();

    // calculating the indent from the last segment
    position.x += _segmentIndent * -direction.x;
    position.y += _segmentIndent * -direction.y;

    pNewSegment->position = position;
    pNewSegment->direction = direction;

    pNewSegment->texture = _tailTexture;
    pNewSegment->angle = direction.getAngle();

    _segments.push_back(pNewSegment);
}

void Snake::setDirection(float x, float y){
    // check if this direction is legal
    if ( _segments.front()->direction.x != (x*-1) && _segments.front()->direction.y != (y*-1)){ 
        _segments.front()->buffdirection = {x, y};
    }
}

// deleting a front segment
void Snake::removeSegment(){
    delete _segments.front();
    _segments.pop_front();
}

// get head position
Vector2f Snake::getPosition() const{
    return _segments.front()->position;
}

// get list of the snake segments
std::list<SnakeSegment*> Snake::getSegments(){
    return _segments;
}

// get pointer to the object of head
SnakeSegment* Snake::getHead(){
    return _segments.front();
}

// destructor
Snake::~Snake(){
    _segments.clear(); 
}

