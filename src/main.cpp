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

enum KEYS
{
    ARROW_RIGHT = 79, ARROW_LEFT = 80,
    ARROW_DOWN = 81, ARROW_UP = 82,
    ESC = 41
};

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

void handleKeyboardEvents(Snake* snake, const Uint8* isPressed){

    if ( isPressed[ARROW_RIGHT] ){
        snake->setDirection(1, 0);

    } else if ( isPressed[ARROW_LEFT] ){
        snake->setDirection(-1, 0);

    } else if ( isPressed[ARROW_DOWN] ){
        snake->setDirection(0, 1);

    } else if ( isPressed[ARROW_UP] ){
        snake->setDirection(0, -1);
    }

    if ( isPressed[ARROW_UP] && isPressed[ARROW_RIGHT] ){   
        snake->setDirection(1, -1);

    } else if ( isPressed[ARROW_UP] && isPressed[ARROW_LEFT] ){
        snake->setDirection(1, -1);

    }  else if ( isPressed[ARROW_DOWN] && isPressed[ARROW_LEFT] ){
        snake->setDirection(1, 1);

    }  else if ( isPressed[ARROW_DOWN] && isPressed[ARROW_RIGHT] ){
        snake->setDirection(-1, 1);
    } 

    if ( isPressed[ESC] ){
        IsGame = false;
    }
}

void handleEvents(SDL_Event event, Snake* snake) {      // handle input
	while (SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:     // if close button pressed
			IsGame = false;
			break;
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
        snake->setDirection(0.0f, 0.0f);
    }
    
    // check for collision with apple
    if ( isCollide( snake->getHitbox(), apple->getHitbox() ) ){
          
        std::srand(std::time(nullptr));

        int random_x = ( BORDER_SIZE * 4 ) + std::rand() % ( SCREEN_WIDTH - BORDER_SIZE * 8 );
        int random_y = ( BORDER_SIZE * 4 ) + std::rand() % ( SCREEN_LENGHT - BORDER_SIZE * 8 );

        apple->setPos(random_x, random_y);
        
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

    //screen->render(snake->getTextureHead(), snake->getPos().x, snake->getPos().y, TEXTURE_SIZE, TEXTURE_SIZE, snake->getAngle());
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
    Snake* snake = new Snake(screen, SCREEN_WIDTH/2, BORDER_SIZE*3, 52.0f, 52.0f, SNAKE_SPEED);
    //                      Screen*, Xpos,           Ypos,          width, length, speed
    Apple* apple = new Apple(screen, SCREEN_WIDTH/2, BORDER_SIZE*8, 32.0f, 32.0f);
    //                      Screen*, Xpos,           Ypos,          width, lenght

    const int       FRAME_DELAY = 1000 / FPS;  // MAX FRAME TIME
    Uint32          frameStart;
    int             deltaTime;

    SDL_Event       event;
    const Uint8*    keysState = SDL_GetKeyboardState(NULL);
    SDL_Texture*    field = screen->loadTexture("./assets/field.png");

    while ( IsGame ){

        frameStart = SDL_GetTicks(); // get start frame ticks

        handleEvents(event, snake);

        handleKeyboardEvents(snake, keysState);

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