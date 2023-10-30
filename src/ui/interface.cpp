#include "interface.hpp"


Interface::Interface()
: isShown(true)
{}

void Interface::setVisibility(bool visible){
    isShown = visible;
}

Text* Interface::createText(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height){
    Text* pNewText = new Text(color, font, text, x, y, width, height);

    return pNewText;
}

Interface::~Interface(){
    delete this;
}