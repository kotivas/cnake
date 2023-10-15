/* snake.cpp
дефолтная змейка с использованием sdl2 либы
фронтенд: 
главное меню
возможность получать очки съедая яблоки, при врезании в стену проигрыш, с каждым очком растёт длина змейки. 
бекенд: функция загрузки текстур, выход из игры(деструктор), инициализация, проверка на врезание в стену или самого себя
проверка на коллизию с яблоком, если яблоко то добавить длинну и очко, функция обновления экрана 
Класс змейка:
м_длина
деструктор
Класс яблоко:
создание с координатами x,y
получение координата
переместить яблоко вместо удаления?
деструктор

попытаться заюзюать фулл ооп?
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>

#include "vector2.h"
#include "screen.h"
#include "snake.h"
#include "apple.h"

#include "config.h"

bool IsGame = true;

bool init(){

    // catch init error
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
		switch(event.type)
		{
		case SDL_QUIT:
			IsGame = false;
			break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode){
            case 79: // right arrow button 
                //std::cout << "Pressed right arrow" << std::endl;
                snake->setDirection(1, 0);
                break;
            case 80: // left arrow button
                //std::cout << "Pressed left arrow" << std::endl;
                snake->setDirection(-1, 0);
                break;
            case 81: // down arrow button
                //std::cout << "Pressed down arrow" << std::endl;
                snake->setDirection(0, 1);
                break;
            case 82: // up arrow button
                //std::cout << "Pressed up arrow" << std::endl;
                snake->setDirection(0, -1);
                break;
            case 41: // esc button
                IsGame = false;
                break;
            default:
                std::cout <<  event.key.keysym.scancode << std::endl;
                break;
            }
            break;
        }
    }
}

bool checkCollide( int firstX, int firstY, int secondX, int secondY ){  
    if ( (firstX + GRID_SIZE >= secondX) && (secondX + GRID_SIZE >= firstX) &&
         (firstY + GRID_SIZE >= secondY) && (secondY + GRID_SIZE >= firstY) ){
        return true;
    }

    return false;
}

void update(Screen* screen, Snake* snake, Apple* apple){

    snake->update();    

    screen->update();

    if ( checkCollide( snake->getPos().x, snake->getPos().y, apple->getPos().x, apple->getPos().y ) ){

        std::srand(std::time(nullptr));
        int random = (std::rand() % 16) * GRID_SIZE;

        if ( random > 0 && random < SCREEN_LENGHT ){
            apple->setPos(random, random);
        } else {
            apple->setPos( GRID_SIZE*9, GRID_SIZE*5);
        }
    }

    /*----------------DEBUG-INFO--------------------*/
    // std::cout << "APPLE:" << std::endl;
    // std::cout << apple->getPos().x << std::endl;
    // std::cout << apple->getPos().y << std::endl;
    /*----------------------------------------------*/

}

void render(Screen* screen, SDL_Texture* field, Snake* snake, Apple* apple){

    screen->clear();

    screen->render(field, 0, 0, SCREEN_WIDTH, SCREEN_LENGHT, 0);

    screen->render(apple->getTexture(), apple->getPos().x, apple->getPos().y, GRID_SIZE, GRID_SIZE, 0);

    screen->render(snake->getTextureHead(), snake->getPos().x, snake->getPos().y, GRID_SIZE, GRID_SIZE, snake->getAngle());

    screen->update();
}

void quit(Screen* screen, SDL_Texture* field, Snake* snake, Apple* apple){

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
    Snake* snake = new Snake(screen);
    Apple* apple = new Apple(screen);

    SDL_Event event;
    SDL_Texture* field = screen->loadTexture("./assets/field48.png");

    while ( IsGame ){

        frameStart = SDL_GetTicks();

        handleEvents(event, snake);

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