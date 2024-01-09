#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <ctime>
#include <string>

#include "renderwindow.hpp"
#include "snake.hpp"
#include "apple.hpp"

#include "config.h"

class Game{
private:
    bool            m_isRunning;
    bool            m_paused;
    int             m_score;
    int             m_bestScore;

    Snake*          m_snake;
    Apple*          m_apple;
    RenderWindow*   m_window;
    
    // contains milliseconds since the start of the step
    Uint32          m_stepStart;
    SDL_Event       m_event;

    // gui
    SDL_Texture*    m_fieldTexture;
    SDL_Texture*    m_appleTexture;
    SDL_Texture*    m_bestScoreTexture;

    // snake sfx
    Mix_Chunk*      m_turnSound;
    Mix_Chunk*      m_eatSound;
    Mix_Chunk*      m_hitSound;

    // snake gfx
    SDL_Texture*    m_headTexture;
    SDL_Texture*    m_bodyTexture;
    SDL_Texture*    m_tailTexture; 

    TTF_Font*       m_font;

    void            checkCollision();    
    void            handleEvents();
    void            render();    

    void            reset();

    std::string     getScore(int score) const;

    void            spawnFood();

public:
    Game();

    bool            isRunning() const;
    void            update();

    ~Game();
};