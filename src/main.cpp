/* Cnake by kotivas
snake game with using SDL2 library
DISTRIBUTED WITH MIT license
October 2023 - January 2024 */

// I HATE WINDOWS
#ifdef _WIN32
#define MAIN_FUNC WinMain
#else
#define MAIN_FUNC main
#endif

#include "game.hpp"

bool init() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL failed to init. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cerr << "SDL_image failed to init. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf failed to init. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer failed to init. Error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

int MAIN_FUNC() {

    if (!init()) {
        std::cerr << "Exiting..." << std::endl;
        return 1;
    }

    // maximum frame time
    const int       FRAME_DELAY = 1000 / FPS;
    Uint32          frameStart;
    int             deltaTime;

    Game* game = new Game();

    while (game->isActive()) {
        frameStart = SDL_GetTicks(); // get start frame ticks

        game->update();

        deltaTime = SDL_GetTicks() - frameStart; // get frame time
        if (FRAME_DELAY > deltaTime) {
            SDL_Delay(FRAME_DELAY - deltaTime);
        }
    }

    delete game;

    return 0;
}