#pragma once

#include "text.hpp"
#include "button.hpp"

class Interface
{
private:
    bool isShown;
public:
    Interface();

    void    handleEvents();

    Text*   createText(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height);
    Button* createButton(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height, SDL_Texture* texture);

    // void    destroyText(Text* text);
    // void    destroyButton(Button* button);

    void    setVisibility(bool visible);
};