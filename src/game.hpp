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

    Snake*          m_snake;
    Apple*          m_apple;
    RenderWindow*   m_window;
    
    SDL_Event       m_event;

    SDL_Texture*    m_fieldTexture;
    SDL_Texture*    m_appleTexture;

    Mix_Chunk*      m_turnSound;
    Mix_Chunk*      m_eatSound;
    Mix_Chunk*      m_hitSound;

    SDL_Texture*    m_headTexture;
    SDL_Texture*    m_bodyTexture;
    SDL_Texture*    m_tailTexture; 
    SDL_Texture*    m_angledTexture;

    TTF_Font*       m_font;

    void            checkCollision();    
    void            handleEvents();
    void            render();    

    void            reset();

    void            spawnFood();

public:
    Game();

    bool            isRunning() const;
    void            update();

    ~Game();
};