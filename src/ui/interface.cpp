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

Button* Interface::createButton(SDL_Color color, TTF_Font* font, std::string text, float x, float y, int width, int height, SDL_Texture* texture){
    Button* pNewButton = new Button(color, font, text, x, y, width, height, texture);

    return pNewButton;
}

// void Interface::destroyText(Text* text){
//     delete text;
//     text = nullptr;
// }

// void Interface::destroyButton(Button* button){
//     delete button;
//     button = nullptr;
// }