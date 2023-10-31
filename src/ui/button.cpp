#include "button.hpp"


Button::Button(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height, SDL_Texture* texture)
: m_width(width), m_height(height), m_x(x), m_y(y), m_texture( texture )
{   
    
    m_isVisible = true;
    //m_text = new Text(color, font, text, x, y, width, height);
}

bool Button::isVisible() const{
    return m_isVisible;
}

void Button::setVisibility(bool visible){
    m_isVisible = visible;
}

// Text* Button::getText() const{
//     return m_text;
// }

SDL_Texture* Button::getTexture() const{
    return m_texture;
}