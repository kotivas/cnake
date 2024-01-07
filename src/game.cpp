#include "game.hpp"

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

    m_turnSound = m_window->loadSound("./assets/turn.wav");
    m_eatSound = m_window->loadSound("./assets/eat.wav");
    m_hitSound = m_window->loadSound("./assets/hit.wav");

    m_window->setWindowIcon("./assets/icon.png");

    /* --------------------------------------------------------- */

    m_snake = new Snake( m_headTexture, m_bodyTexture, m_tailTexture, m_angledTexture,
                              BLOCK_SIZE*6, BLOCK_SIZE*7, 4.0f );
    //                        Xpos,        Ypos,        Speed 

    m_apple = new Apple( m_appleTexture , BLOCK_SIZE*12, BLOCK_SIZE*7 );
    //                   texture          Xpos,         Ypos,      
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
                        if ( m_snake->getHead()->direction != Vector2f(-1, 0) ){
                            Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(1, 0);
                        }
                        break;
                    case SDLK_a: // a or arrow left
                    case SDLK_LEFT:
                        if ( m_snake->getHead()->direction != Vector2f(1, 0) ){
                            Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(-1, 0);
                        }
                        break;
                    case SDLK_s: // s or arrow down
                    case SDLK_DOWN:
                        if ( m_snake->getHead()->direction != Vector2f(0, -1) ){
                            Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(0, 1);
                        }
                        break;
                    case SDLK_w: // w or arrow up
                    case SDLK_UP:
                        if ( m_snake->getHead()->direction != Vector2f(0, 1) ){
                            Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(0, -1);
                        }
                        break;
                    case SDLK_ESCAPE:
                        //m_isRunning = false;
                        break;
                    case SDLK_SPACE:
                        m_snake->reset();
                        Mix_PlayChannel( -1, m_hitSound, 0 );
                        break;
                }
        }
    }
}

// reset al game
void Game::reset(){ 
    m_apple->reset();
    m_snake->reset();
}

// random food spawn
void Game::spawnFood(){
    std::srand(std::time(nullptr));

    int random_x = ( BLOCK_SIZE + std::rand() % ( SCREEN_WIDTH - BLOCK_SIZE*2 ) ) / BLOCK_SIZE;
    int random_y = ( BLOCK_SIZE + std::rand() % ( SCREEN_LENGHT - BLOCK_SIZE*2 ) ) / BLOCK_SIZE;

    m_apple->setPosition(random_x * BLOCK_SIZE, random_y * BLOCK_SIZE);
}

// check for collisions and some logic
void Game::checkCollision(){ // OPTIMIZE
    // check for collision snake with itself
    for (auto segment : m_snake->getSegments() ){
        if ( m_snake->getHead()->position == segment->position &&
             m_snake->getHead() != segment){
            Mix_PlayChannel( -1, m_hitSound, 0 ); // play hit sound
            reset();           
        }
    }
    // check for collsion with border
    if ( m_snake->getHead()->position.x > (SCREEN_WIDTH - BLOCK_SIZE*2) ||
         m_snake->getHead()->position.x < BLOCK_SIZE ||
         m_snake->getHead()->position.y > (SCREEN_LENGHT - BLOCK_SIZE*2) ||
         m_snake->getHead()->position.y < BLOCK_SIZE
         ){
            Mix_PlayChannel( -1, m_hitSound, 0 ); // play hit sound
            reset();
    }
    // check for collision snake with apple
    if ( m_snake->getHead()->position == m_apple->getPosition() ){     
        m_snake->addScore();
        Mix_PlayChannel( -1, m_eatSound, 0 ); // play eat sound
        spawnFood();
    }    
}

// update all game objects
void Game::update(){

    handleEvents();

    m_snake->updatePosition();

    m_window->update();

    checkCollision();    

    render();
}

// render all objects
void Game::render(){

    m_window->clear();

    //               texture,      width,        height,        position
    m_window->render(m_fieldTexture, SCREEN_WIDTH, SCREEN_LENGHT, 0.f, 0.f);
    //               texture,               width,        texture,      position

    m_window->render(m_apple->getTexture(), BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0 );
    m_window->render(m_font, m_snake->getScore(), {75, 105, 47}, 90, BLOCK_SIZE, BLOCK_SIZE*2, 0);

    //               texture,               width,        height,       position
    m_window->render(m_apple->getTexture(), BLOCK_SIZE, BLOCK_SIZE, m_apple->getPosition().x, m_apple->getPosition().y);

    // render body
    for ( const auto segment : m_snake->getSegments() ){
        //               texture,        width,        height,       position,        angle
        if ( segment != m_snake->getHead() ){
            m_window->render(segment->texture, BLOCK_SIZE, BLOCK_SIZE, segment->position.x, segment->position.y, segment->angle);
        }
    }

    // render head
    m_window->render(m_snake->getHead()->texture, BLOCK_SIZE, BLOCK_SIZE, m_snake->getHead()->position.x, m_snake->getHead()->position.y, m_snake->getHead()->angle);

    m_window->update();
}

// destructor
Game::~Game(){

    SDL_DestroyTexture( m_fieldTexture );

    Mix_FreeChunk( m_eatSound );
    Mix_FreeChunk( m_turnSound );
    Mix_FreeChunk( m_hitSound );

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