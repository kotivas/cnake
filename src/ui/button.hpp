#pragma once
#include "text.hpp"
#include <iostream>

class Button
{
private:
    //Text*           m_text;

    bool            m_isVisible;

    int             m_width;
    int             m_height;
    float           m_x;
    float           m_y;

    SDL_Texture*    m_texture;
public:
    Button(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height, SDL_Texture* texture);

    bool            isVisible() const;

    Text*           getText() const;
    SDL_Texture*    getTexture() const;

    void            setVisibility(bool visible);
};