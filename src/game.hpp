#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <random>
#include <string>
#include <stack>

#include "renderwindow.hpp"
#include "snake.hpp"
#include "apple.hpp"

#include "config.h"

class Game{
private:
    bool            isRunning;
    int             score;
    int             bestScore;
    int             volume;

    Snake*          snake;
    Apple*          apple;
    RenderWindow*   window;

    enum            overlayType{
        Menu ,
        Settings
    };

    std::stack<overlayType> overlayStack;

    SDL_Event       event;

    // random generator
    std::mt19937*   randomGenerator;

    // gui
    SDL_Texture*    fieldTexture;
    SDL_Texture*    appleTexture;
    SDL_Texture*    bestScoreTexture;
    SDL_Texture*    menuTexture;

    // snake sfx
    Mix_Chunk*      turnSound;
    Mix_Chunk*      eatSound;
    Mix_Chunk*      hitSound;

    // snake gfx
    SDL_Texture*    headTexture;
    SDL_Texture*    bodyTexture;
    SDL_Texture*    tailTexture; 

    TTF_Font*       font;

    void            checkCollision();    
    void            handleEvents();
    void            drawSnake();    
    void            drawUI();
    void            drawMenu();

    void            reset();

    std::string     getScore(int score) const;

    void            repawnFood();

public:
    Game();

    bool            isActive() const;
    void            update();

    ~Game();
};