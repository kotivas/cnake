/* Snake Game by kotivas

*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>

#include "vector2f.h"
#include "screen.h"
#include "snake.h"
#include "apple.h"

#include "config.h"


bool IsGame = true;         // Is game running?

enum KEYS{
    ARROW_RIGHT = 79, ARROW_LEFT = 80,
    ARROW_DOWN = 81, ARROW_UP = 82,
    ESC = 41
};

bool init(){                                                           // catch init errors

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

    if ( isPressed[ARROW_RIGHT]){
        snake->setDirection(1, 0);
        snake->setAngle(90);

    } else if ( isPressed[ARROW_LEFT] ){
        snake->setDirection(-1, 0);
        snake->setAngle(-90);

    } else if ( isPressed[ARROW_DOWN] ){
        snake->setDirection(0, 1);
        snake->setAngle(180);

    } else if ( isPressed[ARROW_UP] ){
        snake->setDirection(0, -1);
        snake->setAngle(0);
    }

    if ( isPressed[ARROW_UP] && isPressed[ARROW_RIGHT] ){   
        snake->setDirection(1, -1);
        snake->setAngle(45);

    } else if ( isPressed[ARROW_UP] && isPressed[ARROW_LEFT] ){
        snake->setDirection(1, -1);
        snake->setAngle(-45);

    }  else if ( isPressed[ARROW_DOWN] && isPressed[ARROW_LEFT] ){
        snake->setDirection(1, 1);
        snake->setAngle(225);

    }  else if ( isPressed[ARROW_DOWN] && isPressed[ARROW_RIGHT] ){
        snake->setDirection(-1, 1);
        snake->setAngle(135);
    } 

    if ( isPressed[ESC] ){
        IsGame = false;
    }
}

void handleEvents(SDL_Event event, Snake* snake) {                     // handle input
	while (SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			IsGame = false;
			break;
        }
    }
}

bool isCollide( Hitbox hitbox1, Hitbox hitbox2 ){ // check for collision betwen two objects
    if ( (hitbox1.x + hitbox1.width >= hitbox2.x) && (hitbox2.x + hitbox2.width >= hitbox1.x) &&
         (hitbox1.y + hitbox1.lenght >= hitbox2.y) && (hitbox2.y + hitbox2.lenght >= hitbox1.y) ){
        return true;
    }
    return false;
}

void checkCollision(Snake* snake, Apple* apple){
    if ( isCollide( snake->getHitbox(), {0, 0, SCREEN_WIDTH, BORDER_SIZE} ) ||
        isCollide( snake->getHitbox(), {0, 0, BORDER_SIZE, SCREEN_LENGHT} ) ||
        isCollide( snake->getHitbox(), {0, SCREEN_LENGHT - BORDER_SIZE, SCREEN_WIDTH, 0} ) ||
        isCollide( snake->getHitbox(), {SCREEN_WIDTH - BORDER_SIZE, 0, 0, SCREEN_LENGHT} ) ) {
        std::cout << "BORDER COLLIDED" << std::endl;
    }

    if ( isCollide( snake->getHitbox(), apple->getHitbox() ) ){
          
        std::srand(std::time(nullptr));

        apple->setPos((std::rand() % SCREEN_WIDTH), (std::rand() % SCREEN_LENGHT));

        apple->updateHitbox();
    }    
}

void update(Screen* screen, Snake* snake, Apple* apple){               // update AKA tick

    snake->updateHitbox();
    snake->updatePosition();

    screen->update();

    checkCollision(snake, apple);

    // ------------------= DEBUG =------------------
    // std::cout << "\n  Apple:" << std::endl;
    // std::cout << "x: " << apple->getPos().x << std::endl;
    // std::cout << "y: " << apple->getPos().y << std::endl;

    // std::cout << "  Snake:" << std::endl;
    // std::cout << "x: " << snake->getPos().x << std::endl;
    // std::cout << "y: " << snake->getPos().y << std::endl;
    // std::cout << "[" << snake->getDirection().x << "]" << "[" << snake->getDirection().y << "]" << std::endl;

    // ------------------= ----- =------------------
}

void render(Screen* screen, SDL_Texture* field, Snake* snake, Apple* apple){ // render objects

    screen->clear();

    screen->render(field, 0, 0, SCREEN_WIDTH, SCREEN_LENGHT, 0);

    screen->render(apple->getTexture(), apple->getPos().x, apple->getPos().y, TEXTURE_SIZE, TEXTURE_SIZE, 0);

    screen->render(snake->getTextureHead(), snake->getPos().x, snake->getPos().y, TEXTURE_SIZE, TEXTURE_SIZE, snake->getAngle());
    screen->update();
}

void quit(Screen* screen, SDL_Texture* field, Snake* snake, Apple* apple){ // destructor

    SDL_DestroyTexture( field );

    delete(screen);
    delete(snake);
    delete(apple);

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
    const int FRAME_DELAY = 1000 / FPS;

    Uint32 frameStart;
    int deltaTime;

    Screen* screen = new Screen(TITLE, SCREEN_WIDTH, SCREEN_LENGHT);
    
    Snake* snake = new Snake(screen, 35.0f, 35.0f, 4.0f);
    //                      Screen*, width, length, speed (px per frame)
    Apple* apple = new Apple(screen, 35.0f, 35.0f);
    //                      Screen*, width, lenght

    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    SDL_Texture* field = screen->loadTexture("./assets/field48.png");

    while ( IsGame ){

        frameStart = SDL_GetTicks();

        handleEvents(event, snake);

        handleKeyboardEvents(snake, keys);

        update(screen, snake, apple);

        render(screen, field, snake, apple);

        deltaTime = SDL_GetTicks() - frameStart;

        if ( FRAME_DELAY > deltaTime ){
            SDL_Delay( FRAME_DELAY - deltaTime );
        }
    } 

    quit(screen, field, snake, apple);

    return 0;
}
