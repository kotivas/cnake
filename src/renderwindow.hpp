#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>

class RenderWindow {
private:
    SDL_Window*     _window;
    SDL_Renderer*   _renderer;
public:
    RenderWindow(std::string title, int screen_width, int screen_lenght);

    void            render(SDL_Texture* texture, int w, int h, float x,float y, float angle = 0);
    void            render(TTF_Font* font, std::string text, SDL_Color color, int w, int h, float x, float y);

    void            update();
    void            clear();

    SDL_Texture*    loadPNG(std::string path);
    TTF_Font*       loadTTF(std::string path, int size);
    Mix_Chunk*      loadWAV(std::string path);

    void            setWindowIcon(std::string path);

    ~RenderWindow();
};