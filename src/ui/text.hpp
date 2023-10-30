#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text{
private:
    bool    m_isVisible;

    std::string m_text;

    SDL_Color m_color;
    TTF_Font* m_font;
public:
    Text(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height);

    bool            isVisible() const;
    void            setVisibility(bool visible);

    float           x;
    float           y;
    int             width;
    int             height;

    TTF_Font*       getFont() const;
    SDL_Color       getColor() const;
    std::string     getString() const;

    void            setString(std::string text);
    void            setFont(TTF_Font* font);
    void            setColor(SDL_Color color);


    ~Text();
};