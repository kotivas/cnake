#include "game.hpp"

Game::Game()
: isRunning(true), score(0), bestScore(0)
{

    window = new RenderWindow("CNAKE (dev build)", SCREEN_WIDTH, SCREEN_HEIGHT);

    /* --------------------=LOADING ASSETS=--------------------- */
    font = window->loadFont("./assets/atariclassic.ttf", 24);

    fieldTexture = window->loadTexture("./assets/field.png");
    appleTexture = window->loadTexture("./assets/apple.png");

    headTexture = window->loadTexture("./assets/head.png");
    bodyTexture = window->loadTexture("./assets/body.png");
    tailTexture = bodyTexture;

    bestScoreTexture = window->loadTexture("./assets/bestscore.png");

    gameOverTexture = window->loadTexture("./assets/gameover.png");
    vignetteTexture = window->loadTexture("./assets/pausescreen.png");
    controlsTexture = window->loadTexture("./assets/controls.png");
    creditsTexture = window->loadTexture("./assets/credits.png");

    eatSound = window->loadSound("./assets/eat.wav");
    hitSound = window->loadSound("./assets/hit.wav");

    window->setWindowIcon("./assets/icon.png");

    /* --------------------------------------------------------- */

    snake = new Snake( headTexture, bodyTexture, tailTexture );

    apple = new Apple( appleTexture , BLOCK_SIZE*12, BLOCK_SIZE*7 ); 


    std::random_device randDev;
    randomGenerator = new std::mt19937(randDev());

    volume = 50;
    snake->updatePosition();
    overlayStack.push(overlayType::Controls);
}

// return boolean game status
bool Game::isActive() const{
    return isRunning;
}

// handle window events
void Game::handleEvents(){
	while (SDL_PollEvent(&event)){  
		switch(event.type){
		    case SDL_QUIT:     // if close button pressed
			    isRunning = false;
			    break;
            case SDL_KEYDOWN: // if key pressed down
                switch ( event.key.keysym.sym ){ // get key code
                    case SDLK_RIGHT: // d or arrow right
                    case SDLK_d:
                        if ( overlayStack.empty() ){
                            snake->setDirection(1, 0);
                        } else if ( overlayStack.top() == overlayType::Controls ){
                            overlayStack.pop();
                            snake->setDirection(1, 0);
                        }
                        break;
                    case SDLK_a: // a or arrow left
                    case SDLK_LEFT:
                        if ( overlayStack.empty() ){
                            snake->setDirection(-1, 0);
                        } else if ( overlayStack.top() == overlayType::Controls ){
                            overlayStack.pop();
                            snake->setDirection(-1, 0);
                        }
                        break;
                    case SDLK_s: // s or arrow down
                    case SDLK_DOWN:
                        if ( overlayStack.empty() ){
                            snake->setDirection(0, 1);
                        } else if ( overlayStack.top() == overlayType::Controls ){
                            overlayStack.pop();
                            snake->setDirection(0, 1);
                        }
                        break;
                    case SDLK_w: // w or arrow up
                    case SDLK_UP:
                        if ( overlayStack.empty() ){
                            snake->setDirection(0, -1);
                        } else if ( overlayStack.top() == overlayType::Controls ){
                            overlayStack.pop();
                            snake->setDirection(0, -1);
                        }
                        break;
                    case SDLK_ESCAPE:
                        if ( overlayStack.empty() ){
                            overlayStack.push( overlayType::PauseScreen );
                        } else if ( overlayStack.top() == overlayType::PauseScreen  ) {    
                            overlayStack.pop();
                        }
                        break;
                    case SDLK_F1:
                        if ( overlayStack.empty() || overlayStack.top() != overlayType::Cretids ){
                            overlayStack.push( overlayType::Cretids );
                        } else if ( overlayStack.top() == overlayType::Cretids ){
                            overlayStack.pop();
                        }
                        break;
                }
            case SDL_MOUSEBUTTONDOWN: // if mouse button pressed down
                switch ( event.button.button ){
                case SDL_BUTTON_LEFT:
                    if ( !overlayStack.empty() && overlayStack.top() == overlayType::GameOver ){
                        reset();
                        snake->updatePosition();
                        overlayStack.pop();
                        overlayStack.push( overlayType::Controls );
                    }
                    break;
                }
        }
    }
}

// reset al game
void Game::reset(){ 
    apple->position = apple->initPosition;
    snake->reset();
    score = 0;
}

// random food spawn
void Game::respawnFood(){

    // set range for x and y
    std::uniform_int_distribution<> generateX(BLOCK_SIZE, SCREEN_WIDTH-BLOCK_SIZE*2);
    std::uniform_int_distribution<> generateY(BLOCK_SIZE, SCREEN_HEIGHT-BLOCK_SIZE*2);

    // get random x and y
    float random_x = ( generateX(*randomGenerator) / BLOCK_SIZE ) * BLOCK_SIZE;
    float random_y = ( generateY(*randomGenerator) / BLOCK_SIZE ) * BLOCK_SIZE;

    // set random position
    apple->position = {random_x, random_y};
}

// check for collisions and some logic
void Game::checkCollision(){ // OPTIMIZE
    // check for collision snake with itself
    for (auto segment : snake->getSegments() ){
        if ( snake->getHead() != segment ){
            if ( snake->getHead()->position == segment->position){
                Mix_PlayChannel( -1, hitSound, 0 ); // play hit sound
                overlayStack.push( overlayType::GameOver ); 
            } else if ( segment->position == apple->position){
                respawnFood();
            }
        }
    }
    // check for collsion with border
    if ( snake->getHead()->position.x > (SCREEN_WIDTH - BLOCK_SIZE*2) ||
         snake->getHead()->position.x < BLOCK_SIZE ||
         snake->getHead()->position.y > (SCREEN_HEIGHT - BLOCK_SIZE*2) ||
         snake->getHead()->position.y < BLOCK_SIZE
         ){
            Mix_PlayChannel( -1, hitSound, 0 ); // play hit sound
            overlayStack.push( overlayType::GameOver ); 
    }
    // check for collision snake with apple
    if ( snake->getHead()->position == apple->position ){     
        snake->addScore();

        score++;
        if ( score >= bestScore ){
            bestScore = score;
        }

        Mix_PlayChannel( -1, eatSound, 0 ); // play eat sound
        respawnFood();
    }    
}

// update all game objects
void Game::update(){
    /* Frame Independent Movement (NOT CURRENTLY IN USE)
    1. Uint32 m_stepStart = SDL_GetTicks() // declare a step start
    2. float timeStep = (SDL_GetTicks() - m_stepStart) / 1000.f; // calculate the time step
    3. multiply snake position at time step
    4. m_stepStart = SDL_GetTicks(); // restart timer
    */

    window->clear();

    handleEvents();
    Mix_Volume(-1, volume); // update the volume

    drawUI();
    drawSnake();

    // if overlay stack is empty (no overlay)
    if ( overlayStack.empty() ){
        snake->updatePosition();
        checkCollision();
    } else if ( overlayStack.top() == overlayType::GameOver ) {
        window->render(vignetteTexture, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f); // darkened overlay
        window->render(gameOverTexture, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f); // menu overlay

        window->render(apple->texture, 64, 64, 320, 244, 0); // apple icon
        window->render(font, getScore(score), {233, 249, 217}, 90, BLOCK_SIZE, 384, 255); // current score text

        window->render(bestScoreTexture, 64, 64, 480, 244, 0); // best icon
        window->render(font, getScore(bestScore), {233, 249, 217}, 90, BLOCK_SIZE, 480+64, 255); // best score text
    } else if ( overlayStack.top() == overlayType::PauseScreen ){
        window->render(vignetteTexture, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f);
    } else if ( overlayStack.top() == overlayType::Controls ){
        window->render(controlsTexture, 256, 128, SCREEN_WIDTH/3, BLOCK_SIZE*3);
    } else if ( overlayStack.top() == overlayType::Cretids ){
        window->render(vignetteTexture, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f);
        window->render(creditsTexture, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f);
    }
    
    window->update();
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

// draws snake and apple
void Game::drawSnake(){
    //               texture,               width,        height,       position
    window->render(apple->texture, BLOCK_SIZE, BLOCK_SIZE, apple->position.x, apple->position.y);

    // render body
    for ( const auto segment : snake->getSegments() ){
        if ( segment != snake->getHead() ){
            //               texture,          width,      height,     position,                                 angle
            window->render(segment->texture, BLOCK_SIZE, BLOCK_SIZE, segment->position.x, segment->position.y, segment->angle);
        }
    }

    // render head
    window->render(snake->getHead()->texture, BLOCK_SIZE, BLOCK_SIZE, snake->getHead()->position.x, snake->getHead()->position.y, snake->getHead()->angle);
}

void Game::drawUI(){
    window->render(fieldTexture, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f);
    window->render(apple->texture, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0 );
    window->render(font, getScore(score), {75, 105, 47}, 90, BLOCK_SIZE, BLOCK_SIZE*2, 0);

    window->render(bestScoreTexture, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE*4, 0);
    window->render(font, getScore(bestScore), {75, 105, 47}, 90, BLOCK_SIZE, BLOCK_SIZE*5, 0);
}

// destructor
Game::~Game(){

    SDL_DestroyTexture( fieldTexture );
    SDL_DestroyTexture( appleTexture );
    SDL_DestroyTexture( bestScoreTexture );
    SDL_DestroyTexture( gameOverTexture );
    SDL_DestroyTexture( vignetteTexture );
    SDL_DestroyTexture( controlsTexture );
    SDL_DestroyTexture( creditsTexture );

    SDL_DestroyTexture( headTexture );
    SDL_DestroyTexture( bodyTexture );
    SDL_DestroyTexture( tailTexture );

    Mix_FreeChunk( eatSound );
    Mix_FreeChunk( hitSound );

    TTF_CloseFont(font);

    delete window;
    delete snake;
    delete apple; 
    delete randomGenerator;

    // m_window        = nullptr;
    // snake         = nullptr;
    // fieldTexture  = nullptr;
    // bestScoreTexture = nullptr;
    // apple         = nullptr;

    IMG_Quit();
    SDL_Quit();
}