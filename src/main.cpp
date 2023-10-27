/* Cnake by kotivas
snake game with using SDL2 library
DISTRIBUTED WITH 
October 2023 */

/* --------------------------------
TODO:
- рефакторинг
- анимации
- - плавный поворот
- - плавное добавления сегментов - мб брать угол предыдущего сегмента и юзать его при спавне
- - поедание яблока
- - идл анимации?
- класс game?
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
----------------------------------- */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "game.hpp"

bool init(){ 

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) { 
		std::cout << "SDL_Init failed to init. SDL_ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

	if ( !(IMG_Init(IMG_INIT_PNG)) ) {
		std::cout << "IMG_init failed to init. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if ( TTF_Init() < 0 ){
        std::cout << "TTF_init failed to init. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

int main(){

    if ( !init() ){
        std::cout << "FAILED TO INIT\nExiting..." << std::endl;
        return 1;
    }
    
    // maximum frame time
    const int       FRAME_DELAY = 1000 / FPS;
    Uint32          frameStart;
    int             deltaTime;

    Game* game = new Game();

    while ( game->isRunning() ){
        frameStart = SDL_GetTicks(); // get start frame ticks

        game->update();

        deltaTime = SDL_GetTicks() - frameStart; // get frame time
        if ( FRAME_DELAY > deltaTime ){
            SDL_Delay( FRAME_DELAY - deltaTime );
        }
    }

    delete game;

    return 0;
}