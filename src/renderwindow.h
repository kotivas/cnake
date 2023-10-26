#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>
#include "vector2f.h"

class RenderWindow {
private:
    SDL_Window*     m_screen;
    SDL_Renderer*   m_renderer;
public:
    RenderWindow(std::string title, int screen_width, int screen_lenght);

    void            render(SDL_Texture* texture, int w, int h, Vector2f position, float angle = 0);
    void            render(TTF_Font* font, std::string text, SDL_Color color, int w, int h, Vector2f position);

    void            update();
    void            clear();
    SDL_Texture*    loadTexture(std::string path);
    TTF_Font*       loadFont(std::string path, int size);

    ~RenderWindow();
};