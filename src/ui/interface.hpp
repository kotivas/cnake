#pragma once

#include "text.hpp"

class Interface
{
private:
    bool isShown;
public:
    Interface();

    void    handleEvents();

    Text*   createText(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height);

    void    setVisibility(bool visible);

    ~Interface();
};