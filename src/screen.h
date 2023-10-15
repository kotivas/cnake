#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Screen {
private:
    SDL_Window* m_screen;
    SDL_Renderer* m_render;
public:
    Screen(const char* TITLE, const unsigned short SCREEN_WIDTH, const unsigned short SCREEN_LENGHT);

    void render(SDL_Texture* texture, int x, int y, int w, int h, int angle);
    void update();
    void clear();

    SDL_Texture* loadTexture(const char* path);

    ~Screen();

    SDL_Event event;
};