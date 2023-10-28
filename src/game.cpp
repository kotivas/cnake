#include "game.hpp"
/* --------------------------------
TODO:
- рефакторинг
- анимации
- - плавный поворот
- - плавное добавления сегментов - мб брать угол предыдущего сегмента и юзать его при спавне
- - поедание яблока
- - идл анимации?
- возможность менять размер поля
- иконка
- система частиц (снег, листья и т.п)
TODO: TO FINISH
- пофиксить движение
- отзывчевее движенин
- - голова отдельно, стабилизация
тело не двигается?  
- звук
- менюшка - экран смерти, рекорд
------------------------------------------------------------------------------------------------------------------------------
Голова может поварачивать вокруг точки тела (шеи)

В ранних поворотах, голова начинает вращаться сразу, но достигает 90° только когда шея выровнена по сетке,
поскольку тело змеи от шеи до хвоста продолжает двигаться в том же направлении.

Для поздних повортах почти тоже самое. Кончик головы (рот) проходит пересечение, но не шея.
Таким образом, голова может быстро поворачиваться на 90°, когда шея достигает пересечения.

Анимация глаз и языка змеи также помогает отвлечь вас от вращения головы.
(глаза сохраняют постоянное направление, несмотря на вращение головы, а язык привлекает ваше внимание к точке впереди головы).
----------------------------------- */

Game::Game()
: m_isRunning(true)
{
    m_window = new RenderWindow("CNAKE (dev build)", SCREEN_WIDTH, SCREEN_LENGHT);
    //                                       title,  screen width, screen lenght

    /* --------------------=LOADING ASSETS=--------------------- */
    m_font = m_window->loadFont("./assets/atariclassic.ttf", 24);

    m_fieldTexture = m_window->loadTexture("./assets/field.png");
    m_appleTexture = m_window->loadTexture("./assets/apple.png");

    m_headTexture = m_window->loadTexture("./assets/head.png");
    m_bodyTexture = m_window->loadTexture("./assets/body.png");
    m_tailTexture = m_window->loadTexture("./assets/tail.png");
    /* --------------------------------------------------------- */

    m_snake = new Snake( m_headTexture, m_bodyTexture, m_tailTexture,
                              GRID_SIZE*3, GRID_SIZE*7, 3.0f,
    //                        Xpos,           Ypos,          Speed                              
                              { 1, 0 },  2);
    //                        direction, segments 

    m_apple = new Apple( m_appleTexture , GRID_SIZE*12, GRID_SIZE*7 );
    //                       texture       Xpos,           Ypos,      
}

// return boolean game status
bool Game::isRunning() const{
    return m_isRunning;
}

// handle window events
void Game::handleEvents(){
	while (SDL_PollEvent(&m_event)){  
		switch(m_event.type){
		    case SDL_QUIT:     // if close button pressed
			    m_isRunning = false;
			    break;
            case SDL_KEYDOWN: // if key pressed down
                switch ( m_event.key.keysym.sym ){ // get key code
                    case SDLK_RIGHT: // d or arrow right
                    case SDLK_d:
                        m_snake->setDirection( {1, 0} );
                        break;
                    case SDLK_a: // a or arrow left
                    case SDLK_LEFT:
                        m_snake->setDirection( {-1, 0} );
                        break;
                    case SDLK_s: // s or arrow down
                    case SDLK_DOWN:
                        m_snake->setDirection( {0, 1} );
                        break;
                    case SDLK_w: // w or arrow up
                    case SDLK_UP:
                        m_snake->setDirection( {0, -1} );
                        break;
                    case SDLK_ESCAPE:
                        m_isRunning = false;
                        break;
                    case SDLK_SPACE:
                        m_snake->reset();
                        break;
                }
        }
    }
}

// check for collisions and some logic
void Game::checkCollision(){
    // check for collsion with border
    if ( m_snake->getPosition().x > (SCREEN_WIDTH - BORDER_SIZE*2) ||
         m_snake->getPosition().x < BORDER_SIZE ||
         m_snake->getPosition().y > (SCREEN_LENGHT - BORDER_SIZE*2) ||
         m_snake->getPosition().y < BORDER_SIZE
         ){
            m_snake->reset();
    }

    // check for collision with apple
    if ( m_snake->getPosition().y == m_apple->getPosition().y &&
         m_snake->getPosition().x == m_apple->getPosition().x ){
        
        m_snake->addScore();

        // FIXME: баг со спавном яблока в змейке

        std::srand(std::time(nullptr));

        int random_x = ( BORDER_SIZE + std::rand() % ( SCREEN_WIDTH - BORDER_SIZE*2 ) ) / GRID_SIZE;
        int random_y = ( BORDER_SIZE + std::rand() % ( SCREEN_LENGHT - BORDER_SIZE*2 ) ) / GRID_SIZE;

        m_apple->setPosition(random_x * GRID_SIZE, random_y * GRID_SIZE);
    }    
}

// update all game objects
void Game::update(){

    handleEvents();

    m_snake->updatePosition( GRID_SIZE );

    m_window->update();

    checkCollision();    

    render();
}

// render all objects
void Game::render(){
    m_window->clear();
    //               texture,      width,        height,        position
    m_window->render(m_fieldTexture, SCREEN_WIDTH, SCREEN_LENGHT, {0.f, 0.f});
    //               texture,               width,        texture,      position
    m_window->render(m_apple->getTexture(), TEXTURE_SIZE, TEXTURE_SIZE, {BORDER_SIZE, 0} );
    //               font,   text,                color RGB   width, height,      position       
    m_window->render(m_font, m_snake->getScore(), {75, 105, 47}, 90, BORDER_SIZE, {BORDER_SIZE*2, 0});
    //               texture,               width,        height,       position
    m_window->render(m_apple->getTexture(), TEXTURE_SIZE, TEXTURE_SIZE, m_apple->getPosition());

    SnakeSegment* pIter = m_snake->getHead();
    while ( pIter != nullptr ){
        //               texture,        width,        height,       position,        angle
        m_window->render(pIter->texture, TEXTURE_SIZE, TEXTURE_SIZE, pIter->position, pIter->angle);
        pIter = pIter->pNext;
    }

    m_window->update();
}

// destructor
Game::~Game(){

    SDL_DestroyTexture( m_fieldTexture );

    delete m_window;
    delete m_snake;
    delete m_apple;

    m_window        = nullptr;
    m_snake         = nullptr;
    m_fieldTexture  = nullptr;
    m_apple         = nullptr;

    IMG_Quit();
    SDL_Quit();
}