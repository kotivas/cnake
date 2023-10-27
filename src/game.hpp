#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
    Snake*          m_snake;
    Apple*          m_apple;
    RenderWindow*   m_window;
    
    SDL_Event       m_event;

    SDL_Texture*    m_fieldTexture;
    SDL_Texture*    m_appleTexture;
    SDL_Texture*    m_headTexture;
    SDL_Texture*    m_bodyTexture;
    SDL_Texture*    m_tailTexture; 
    TTF_Font*       m_font;

public:
    Game();

    bool            isRunning() const;

    void            handleEvents();
    void            checkCollision();
    void            update();
    void            render();

    inline void     loadAssets();

    ~Game();
};