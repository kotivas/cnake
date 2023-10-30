#include "text.hpp"


Text::Text(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height)
:m_color( color ), m_font( font ), x( x ), y( y ), width( width ), height( height )
{
    m_isVisible = true;
    m_text = text;
}

void Text::setString(std::string text){
    m_text = text;
}

void Text::setColor(SDL_Color color){
    m_color = color;
}

void Text::setFont(TTF_Font* font){
    m_font = font;
}

bool Text::isVisible() const{
    return m_isVisible;
}

void Text::setVisible(bool visible){
    m_isVisible = visible;
}

SDL_Color Text::getColor() const{
    return m_color;
}

std::string Text::getString() const{
    return m_text;
}

TTF_Font* Text::getFont() const{
    return m_font;
}

Text::~Text(){
    delete this;
}