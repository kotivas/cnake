/* snake enitty
положение x,y
направление

добавление очков
изменение положения
изменение направления

получение положения
получение текстур
получение очков
получение направления
*/

#include "snake.h"

Snake::Snake(Screen* screen)
: m_head(nullptr), m_body(nullptr), m_tail(nullptr),
m_pos{GRID_SIZE * 5, GRID_SIZE * 5}, m_currDirection{0, -1},
 m_nextDirection{0, -1}, m_speed(2), m_angle(0)
{
    m_head = screen->loadTexture("./assets/head_up.png");

    if ( m_head == nullptr ){
        std::cout << SDL_GetError() << std::endl;
    }

}

SDL_Texture* Snake::getTextureHead() const{
    return m_head;
}

void Snake::update(){
    //----------------------CHECKS FOR COLLISION WITH BORDER--------------------
    if ( m_pos.x < GRID_SIZE ){
        m_pos.x = SCREEN_WIDTH - ( GRID_SIZE * 2 ); // screen width - border width
    } else if ( m_pos.x > ( SCREEN_WIDTH - GRID_SIZE*2 ) ){
        m_pos.x = GRID_SIZE;
    }
    
    if ( m_pos.y < GRID_SIZE ){
        m_pos.y = SCREEN_LENGHT - ( GRID_SIZE * 2 );  // screen width - border width
    } else if ( m_pos.y > ( SCREEN_LENGHT - GRID_SIZE*2 ) ){
        m_pos.y = GRID_SIZE;
    }
    //-------------------------------------------------------------------------


    //----------------------CHECKS IF SNAKE OUT OF GRID------------------------
    if ( (m_pos.x % GRID_SIZE) == 0){
        m_currDirection.x = m_nextDirection.x;
    } else if ( (m_pos.y % GRID_SIZE) == 0){
        m_currDirection.y = m_nextDirection.y;
    }
    //-------------------------------------------------------------------------

    m_pos.x += m_speed * m_currDirection.x;
    m_pos.y += m_speed * m_currDirection.y;

}

int Snake::getAngle() const{
    return m_angle;
}

void Snake::setAngle(int angle){
    m_angle = angle;
}

Vector2 Snake::getDirection() const{
    return m_currDirection;
}
void Snake::setDirection(int dirX, int dirY){

    if ( m_nextDirection.x != (dirX * -1) ){
         m_nextDirection.x = dirX;
    }
    if ( m_nextDirection.y != (dirY * -1) ){
        m_nextDirection.y = dirY;
    }
    
    switch ( m_nextDirection.x ){
    case -1:
        setAngle(90 * 3);
        break;
    case 1:
        setAngle(90 * 1);
        break;
    }

    switch ( m_nextDirection.y )
    {
    case -1:
        setAngle(90 * 0);
        break;
    case 1:
        setAngle(90 * 2);
        break;
    }

}

void Snake::setPos(int x, int y){
    m_currDirection.x = x;
    m_currDirection.y = y;
}

Vector2 Snake::getPos() const{
    return m_pos;
}

Snake::~Snake(){
    SDL_DestroyTexture( m_head );
    SDL_DestroyTexture( m_body );
    SDL_DestroyTexture( m_tail );

    m_head = nullptr;
    m_body = nullptr;
    m_tail = nullptr;
}