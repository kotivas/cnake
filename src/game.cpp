#include "game.hpp"

Game::Game()
: m_isRunning(true), m_paused(false)
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

    m_bestScoreTexture = m_window->loadTexture("./assets/bestscore.png");

    m_turnSound = m_window->loadSound("./assets/turn.wav");
    m_eatSound = m_window->loadSound("./assets/eat.wav");
    m_hitSound = m_window->loadSound("./assets/hit.wav");

    m_window->setWindowIcon("./assets/icon.png");

    /* --------------------------------------------------------- */

    m_snake = new Snake( m_headTexture, m_bodyTexture, m_tailTexture );

    m_apple = new Apple( m_appleTexture , BLOCK_SIZE*12, BLOCK_SIZE*7 );
    //                   texture          Xpos,         Ypos,      

    m_score = 0;
    m_bestScore = 0;
    m_stepStart = SDL_GetTicks();
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
                        if ( m_snake->getHead()->direction != Vector2f(-1, 0) && !m_paused ){
                            if (SOUND) Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(1, 0);
                        }
                        break;
                    case SDLK_a: // a or arrow left
                    case SDLK_LEFT:
                        if ( m_snake->getHead()->direction != Vector2f(1, 0) && !m_paused){
                            if (SOUND) Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(-1, 0);
                        }
                        break;
                    case SDLK_s: // s or arrow down
                    case SDLK_DOWN:
                        if ( m_snake->getHead()->direction != Vector2f(0, -1) && !m_paused){
                            if (SOUND) Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(0, 1);
                        }
                        break;
                    case SDLK_w: // w or arrow up
                    case SDLK_UP:
                        if ( m_snake->getHead()->direction != Vector2f(0, 1) && !m_paused){
                            if (SOUND) Mix_PlayChannel( -1, m_turnSound, 0 );
                            m_snake->setDirection(0, -1);
                        }
                        break;
                    case SDLK_ESCAPE:
                        m_paused = !m_paused;
                        break;
                    case SDLK_r:
                        reset();
                        break;
                }
        }
    }
}

// reset al game
void Game::reset(){ 
    m_apple->position = m_apple->initPosition;
    m_snake->reset();
    m_score = 0;
}

// random food spawn
void Game::spawnFood(){
    std::srand(std::time(nullptr));

    float random_x = ( BLOCK_SIZE + std::rand() % ( SCREEN_WIDTH - BLOCK_SIZE*2 ) ) / BLOCK_SIZE;
    float random_y = ( BLOCK_SIZE + std::rand() % ( SCREEN_LENGHT - BLOCK_SIZE*2 ) ) / BLOCK_SIZE;

    m_apple->position = {random_x * BLOCK_SIZE, random_y * BLOCK_SIZE};
}

// check for collisions and some logic
void Game::checkCollision(){ // OPTIMIZE
    // check for collision snake with itself
    for (auto segment : m_snake->getSegments() ){
        if ( m_snake->getHead()->position == segment->position &&
             m_snake->getHead() != segment){
            if (SOUND) Mix_PlayChannel( -1, m_hitSound, 0 ); // play hit sound
            reset();           
        }
    }
    // check for collsion with border
    if ( m_snake->getHead()->position.x > (SCREEN_WIDTH - BLOCK_SIZE*2) ||
         m_snake->getHead()->position.x < BLOCK_SIZE ||
         m_snake->getHead()->position.y > (SCREEN_LENGHT - BLOCK_SIZE*2) ||
         m_snake->getHead()->position.y < BLOCK_SIZE
         ){
            if (SOUND) Mix_PlayChannel( -1, m_hitSound, 0 ); // play hit sound
            reset();
    }
    // check for collision snake with apple
    if ( m_snake->getHead()->position == m_apple->position ){     
        m_snake->addScore();

        m_score++;
        if ( m_score >= m_bestScore ){
            m_bestScore = m_score;
        }

        if (SOUND) Mix_PlayChannel( -1, m_eatSound, 0 ); // play eat sound
        spawnFood();
    }    
}

// update all game objects
void Game::update(){

    handleEvents();

    // calculate time step in seconds
    float timeStep = (SDL_GetTicks() - m_stepStart) / 1000.f;

    // if game not paused
    if ( !m_paused ){
        m_snake->updatePosition( timeStep );
        checkCollision();
    }

    m_stepStart = SDL_GetTicks(); // restart timer

    m_window->update();

    render();
}

// get formatted score string
std::string Game::getScore(int score) const{
    if ( score == 0 ){
        return "000";
    } else if (  score <= 9 ){
        return "00" + std::to_string( score );
    } else if ( score <= 99 ){ 
        return "0" + std::to_string( score );
    } else {
        return std::to_string( score );
    }
}

// render all objects
void Game::render(){

    m_window->clear();

    //               texture,      width,        height,        position
    m_window->render(m_fieldTexture, SCREEN_WIDTH, SCREEN_LENGHT, 0.f, 0.f);
    //               texture,               width,        texture,      position

    m_window->render(m_apple->texture, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0 );
    m_window->render(m_font, getScore(m_score), {75, 105, 47}, 90, BLOCK_SIZE, BLOCK_SIZE*2, 0);

    m_window->render(m_bestScoreTexture, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE*4, 0);
    m_window->render(m_font, getScore(m_bestScore), {75, 105, 47}, 90, BLOCK_SIZE, BLOCK_SIZE*5, 0);

    //               texture,               width,        height,       position
    m_window->render(m_apple->texture, BLOCK_SIZE, BLOCK_SIZE, m_apple->position.x, m_apple->position.y);

    // render body
    for ( const auto segment : m_snake->getSegments() ){
        if ( segment != m_snake->getHead() ){
            //               texture,          width,      height,     position,                                 angle
            m_window->render(segment->texture, BLOCK_SIZE, BLOCK_SIZE, segment->position.x, segment->position.y, segment->angle);
        }
    }

    // render head
    m_window->render(m_snake->getHead()->texture, BLOCK_SIZE, BLOCK_SIZE, m_snake->getHead()->position.x, m_snake->getHead()->position.y, m_snake->getHead()->angle);

    if ( m_paused ){
        m_window->render(m_font, "PAUSED", {255, 255, 255}, 250, 100, SCREEN_LENGHT/2, SCREEN_WIDTH/3.5);
    }

    m_window->update();
}

// destructor
Game::~Game(){

    SDL_DestroyTexture( m_fieldTexture );
    SDL_DestroyTexture( m_appleTexture );
    SDL_DestroyTexture( m_bestScoreTexture );

    SDL_DestroyTexture( m_headTexture );
    SDL_DestroyTexture( m_bodyTexture );
    SDL_DestroyTexture( m_tailTexture );

    Mix_FreeChunk( m_eatSound );
    Mix_FreeChunk( m_turnSound );
    Mix_FreeChunk( m_hitSound );

    delete m_window;
    delete m_snake;
    delete m_apple; 

    m_window        = nullptr;
    m_snake         = nullptr;
    m_fieldTexture  = nullptr;
    m_bestScoreTexture = nullptr;
    m_apple         = nullptr;


    IMG_Quit();
    SDL_Quit();
}