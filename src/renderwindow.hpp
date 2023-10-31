#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>

#include "ui/interface.hpp"

class RenderWindow {
private:
    SDL_Window*     m_screen;
    SDL_Renderer*   m_renderer;
public:
    RenderWindow(std::string title, int screen_width, int screen_lenght);

    void            render(SDL_Texture* texture, int w, int h, float x,float y, float angle = 0);
    void            render(TTF_Font* font, std::string text, SDL_Color color, int w, int h, float x, float y);
    void            render(Text* text);
    void            render(Button* button);

    void            update();
    void            clear();
    SDL_Texture*    loadTexture(std::string path);
    TTF_Font*       loadFont(std::string path, int size);
    Mix_Chunk*      loadSound(std::string path);

    ~RenderWindow();
};