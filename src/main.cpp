/* Snake Game by kotivas

*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>

#include "screen.h"
#include "snake.h"
#include "apple.h"

#include "config.h"

#include "snakesegment.h"

bool IsGame = true; // Is game running?

bool init(){       // catch init errors

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

void handleEvents(SDL_Event event, Snake* snake) {      // handle input
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
bool isCollide( Hitbox hitbox1, Hitbox hitbox2 ){ // check for collision betwen two objects
    return (hitbox1.x + hitbox1.width >= hitbox2.x) && (hitbox2.x + hitbox2.width >= hitbox1.x) &&
           (hitbox1.y + hitbox1.lenght >= hitbox2.y) && (hitbox2.y + hitbox2.lenght >= hitbox1.y);
}

void checkCollision(Snake* snake, Apple* apple){

    // check for collision wirh border
    if (
        isCollide( snake->getHitbox(), {0, 0, SCREEN_WIDTH, BORDER_SIZE} ) ||
        isCollide( snake->getHitbox(), {0, 0, BORDER_SIZE, SCREEN_LENGHT} ) ||
        isCollide( snake->getHitbox(), {0, SCREEN_LENGHT - BORDER_SIZE, SCREEN_WIDTH, 0} ) ||
        isCollide( snake->getHitbox(), {SCREEN_WIDTH - BORDER_SIZE, 0, 0, SCREEN_LENGHT} ) 
       ) {
        snake->setDirection( {0.0f, 0.0f} );
    }
    
    // check for collision with apple
    // if ( isCollide( snake->getHitbox(), apple->getHitbox() ) ){
    if ( snake->getPos().x == apple->getPos().x && snake->getPos().y == apple->getPos().y ){
          
        std::srand(std::time(nullptr));

        int random_x = BORDER_SIZE*2 + std::rand() % (SCREEN_WIDTH / GRID_SIZE) - BORDER_SIZE*2;//BORDER_SIZE - std::rand() % ( (SCREEN_WIDTH  / GRID_SIZE)  + BORDER_SIZE * 4);
        int random_y = BORDER_SIZE*2 + std::rand() % (SCREEN_LENGHT / GRID_SIZE) - BORDER_SIZE*2; //BORDER_SIZE - std::rand() % ( (SCREEN_LENGHT  / GRID_SIZE) + BORDER_SIZE * 4 );

        apple->setPos(random_x * GRID_SIZE, random_y * GRID_SIZE);
    }    
}

void update(Screen* screen, Snake* snake, Apple* apple){               // update AKA tick

    snake->updatePosition();
    snake->updateHitbox();

    screen->update();

    apple->updateHitbox();
                    
    checkCollision(snake, apple);    
}

void render(Screen* screen, SDL_Texture* field, Snake* snake, Apple* apple){ // render objects

    screen->clear();

    screen->render(field, 0, 0, SCREEN_WIDTH, SCREEN_LENGHT, 0);

    screen->render(apple->getTexture(), apple->getPos().x, apple->getPos().y, TEXTURE_SIZE, TEXTURE_SIZE, 0);

    SnakeSegment* pIter = snake->getHead();

    while ( pIter != nullptr ){
        screen->render(pIter->texture, pIter->position.x, pIter->position.y, TEXTURE_SIZE, TEXTURE_SIZE, pIter->angle);
        pIter = pIter->pNext;
    }

    screen->update();
}

void quit(Screen* screen, SDL_Texture* field, Snake* snake, Apple* apple){ // destructor

    SDL_DestroyTexture( field );

    delete screen;
    delete snake;
    delete apple;

    screen = nullptr;
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

    Screen* screen = new Screen(TITLE, SCREEN_WIDTH, SCREEN_LENGHT);
    //                          title, screen_width, screen_lenght
    Snake* snake = new Snake(screen, SCREEN_WIDTH/2, BORDER_SIZE*3, 32.0f, 32.0f, SNAKE_SPEED);
    //                      Screen*, Xpos,           Ypos,          width, length, speed
    Apple* apple = new Apple(screen, SCREEN_WIDTH/2, BORDER_SIZE*8, 48.0f, 48.0f);
    //                      Screen*, Xpos,           Ypos,          width, lenght

    const int       FRAME_DELAY = 1000 / FPS;  // MAX FRAME TIME
    Uint32          frameStart;
    int             deltaTime;

    SDL_Event       event;
    SDL_Texture*    field = screen->loadTexture("./assets/field.png");

    while ( IsGame ){

        frameStart = SDL_GetTicks(); // get start frame ticks

        handleEvents(event, snake);

        update(screen, snake, apple);

        render(screen, field, snake, apple);

        deltaTime = SDL_GetTicks() - frameStart; // get frame time

        if ( FRAME_DELAY > deltaTime ){
            SDL_Delay( FRAME_DELAY - deltaTime );
        }
    } 

    quit(screen, field, snake, apple);

    return 0;
}