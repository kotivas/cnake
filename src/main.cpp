/* Cnake by kotivas
snake game with using SDL2 library
DISTRIBUTED WITH GNU PUBLIC LICENSE
October 2023 */

/* TODO:
- рефакторинг
- звук
- возможность менять размер поля?
- анимации
- - плавный поворот
- - плавное добавления сегментов - мб брать угол предыдущего сегмента и юзать его при спавне
- - поедание яблока
- - идл анимации?
- перезапуск
- менюшка
- класс game?
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>

#include "renderwindow.h"
#include "snake.h"
#include "apple.h"
#include "config.h"

// FIXME: в классе game/app, перенести в него соблюдая ООП
// is game running?
bool    IsGame = true;
// catch init errors
bool    init();
// handle window events
void    handleEvents(SDL_Event event, Snake* snake);
// check for collision between snake, apple and walls
void    checkCollision(Snake* snake, Apple* apple);
// update all
void    update(RenderWindow* screen, Snake* snake, Apple* apple);
// render objects
void    render(RenderWindow* screen, SDL_Texture* fieldTexture, Snake* snake, Apple* apple);
// destructor
void    quit(RenderWindow* screen, SDL_Texture* field, Snake* snake, Apple* apple);

bool init(){ 

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) { 
		std::cout << "SDL_Init failed to init. SDL_ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

	if ( !(IMG_Init(IMG_INIT_PNG)) ) {
		std::cout << "IMG_init failed to init. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


void handleEvents(SDL_Event event, Snake* snake) {
	while (SDL_PollEvent(&event)){  
		switch(event.type){
		    case SDL_QUIT:     // if close button pressed
			    IsGame = false;
			    break;

            case SDL_KEYDOWN: // if key pressed down
                switch ( event.key.keysym.sym ){ // get key code
                    case SDLK_RIGHT:
                        snake->setDirection( {1, 0} );
                        break;
                    case SDLK_LEFT:
                        snake->setDirection( {-1, 0} );
                        break;
                    case SDLK_DOWN:
                        snake->setDirection( {0, 1});
                        break;
                    case SDLK_UP:
                        snake->setDirection( {0, -1} );
                        break;
                    case SDLK_ESCAPE:
                        IsGame = false;
                        break;
                }
        }
    }
}

// check for collision between snake, apple and walls
void checkCollision(Snake* snake, Apple* apple){

    // check for collsion with border
    if ( snake->getPosition().x > (SCREEN_WIDTH - BORDER_SIZE*2) ||
         snake->getPosition().x < BORDER_SIZE ||
         snake->getPosition().y > (SCREEN_LENGHT - BORDER_SIZE*2) ||
         snake->getPosition().y < BORDER_SIZE
         ){
    }

    // check for collision with apple
    if ( snake->getPosition().y == apple->getPosition().y &&
         snake->getPosition().x == apple->getPosition().x ){
        
        snake->addScore();

        std::srand(std::time(nullptr));

        int random_x = ( BORDER_SIZE + std::rand() % ( SCREEN_WIDTH - BORDER_SIZE*2 ) ) / GRID_SIZE;
        int random_y = ( BORDER_SIZE + std::rand() % ( SCREEN_LENGHT - BORDER_SIZE*2 ) ) / GRID_SIZE;

        apple->setPosition(random_x * GRID_SIZE, random_y * GRID_SIZE);
    }    
}

void update(RenderWindow* window, Snake* snake, Apple* apple){

    snake->updatePosition();

    window->update();

    checkCollision(snake, apple);    
}

void render(RenderWindow* window, SDL_Texture* fieldTexture, Snake* snake, Apple* apple){

    window->clear();

    window->render(fieldTexture, {0.f, 0.f}, SCREEN_WIDTH, SCREEN_LENGHT, 0.f);

    window->render(apple->getTexture(), apple->getPosition(), TEXTURE_SIZE, TEXTURE_SIZE, 0.f);

    SnakeSegment* pIter = snake->getHead();

    while ( pIter != nullptr ){
        window->render(pIter->texture, pIter->position, TEXTURE_SIZE, TEXTURE_SIZE, pIter->angle);
        pIter = pIter->pNext;
    }

    window->update();
}

void quit(RenderWindow* window, SDL_Texture* field, Snake* snake, Apple* apple){

    SDL_DestroyTexture( field );

    delete window;
    delete snake;
    delete apple;

    window = nullptr;
    snake = nullptr;
    field = nullptr;
    apple = nullptr;

    IMG_Quit();
    SDL_Quit();
}

int main(){

    if ( !init() ){
        std::cout << "FAILED TO INIT\nExiting..." << std::endl;
        return 1;
    }
    
    // maximum frame time
    const int       FRAME_DELAY = 1000 / FPS;
    Uint32          frameStart;
    // number of ticks occupied by the frame
    int             deltaTime;

    SDL_Event       event;

    // textures
    SDL_Texture*    fieldTexture;
    SDL_Texture*    appleTexture;
    SDL_Texture*    headTexture;
    SDL_Texture*    bodyTexture;
    SDL_Texture*    tailTexture;

    RenderWindow* window = new RenderWindow(TITLE, SCREEN_WIDTH, SCREEN_LENGHT);
    //                          title, screen width, screen lenght

    fieldTexture = window->loadTexture("./assets/field.png");
    appleTexture = window->loadTexture("./assets/apple.png");

    headTexture = window->loadTexture("./assets/head_down.png");
    bodyTexture = window->loadTexture("./assets/body_vertical.png");
    tailTexture = window->loadTexture("./assets/tail_up.png");

    Snake* snake = new Snake( headTexture, bodyTexture, tailTexture,
    //                        headTexture, bodyTexture, tailTexture
                              SCREEN_WIDTH/2, BORDER_SIZE*3, SNAKE_SPEED);
    //                        Xpos,           Ypos,          Speed

    Apple* apple = new Apple(appleTexture ,SCREEN_WIDTH/2, BORDER_SIZE*8);
    //                       texture       Xpos,           Ypos,      



    while ( IsGame ){

        frameStart = SDL_GetTicks(); // get start frame ticks

        handleEvents(event, snake);
        update(window, snake, apple);
        render(window, fieldTexture, snake, apple);

        deltaTime = SDL_GetTicks() - frameStart; // get frame time
        if ( FRAME_DELAY > deltaTime ){
            SDL_Delay( FRAME_DELAY - deltaTime );
        }
    } 

    quit(window, fieldTexture, snake, apple);

    return 0;
}