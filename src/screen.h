#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "vector2f.h"

class Screen {
private:
    SDL_Window*     m_screen;
    SDL_Renderer*   m_render;
public:
    Screen(const char* TITLE, const unsigned short SCREEN_WIDTH, const unsigned short SCREEN_LENGHT);

    void            render(SDL_Texture* texture, Vector2f position, int w, int h, int angle);
    void            update();
    void            clear();
    SDL_Texture*    loadTexture(const char* path);

    ~Screen();
};