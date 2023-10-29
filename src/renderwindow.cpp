/* Screen
is responsible for show window, render things and load textures
*/

#include "renderwindow.hpp"

RenderWindow::RenderWindow(std::string title, int screen_width, int screen_lenght)
: m_screen(nullptr), m_renderer(nullptr)
{
    m_screen = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_lenght, SDL_WINDOW_SHOWN);
	if (m_screen == nullptr){
		std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;
	}

    m_renderer = SDL_CreateRenderer(m_screen, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr){
        std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
    }

    // AntiAliasing
    // SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
}

SDL_Texture* RenderWindow::loadTexture(std::string path){
    SDL_Texture* pNewTexture = nullptr;

	pNewTexture = IMG_LoadTexture( m_renderer, path.c_str() );

	if ( pNewTexture == nullptr )
		std::cout << "Failed to load texture. Error: "<< SDL_GetError() << std::endl;

	return pNewTexture;
}

TTF_Font* RenderWindow::loadFont(std::string path, int size){

    TTF_Font* pNewFont = TTF_OpenFont(path.c_str(), size);

    if ( !pNewFont ){
        std::cout << "Failed to load font. Error: " << SDL_GetError() << std::endl;
    }

    return pNewFont;
}

Mix_Chunk* RenderWindow::loadSound(std::string path){
    Mix_Chunk* pNewSound = Mix_LoadWAV( path.c_str() );

    if ( !pNewSound ){
        std::cout << "Failed to load wav. Error: " << SDL_GetError() << std::endl;
    }

    return pNewSound;
}

// render a sprite 
void RenderWindow::render(SDL_Texture* texture, int w, int h, Vector2f position, float angle){
	SDL_Rect src; 
	src.x = 0;
	src.y = 0;
	//src.w;
	//src.h;

    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
	dst.x = position.x;
	dst.y = position.y;
	dst.w = w; //src.w;
	dst.h = h; //src.h;

    SDL_RenderCopyEx( m_renderer, texture, &src, &dst, angle, NULL, SDL_FLIP_NONE);
}

// render a text
void RenderWindow::render(TTF_Font* font, std::string text, SDL_Color color, int w, int h, Vector2f position){

    // create a surface text
    SDL_Surface* pSurfaceText = TTF_RenderText_Solid(font, text.c_str(), color); 
    // convert surface into a texture
    SDL_Texture* pText = SDL_CreateTextureFromSurface(m_renderer, pSurfaceText);

    SDL_Rect rect; //create a rect
    rect.x = position.x;  //controls the rect's x coordinate 
    rect.y = position.y; // controls the rect's y coordinte
    rect.w = w; // controls the width of the rect
    rect.h = h; // controls the height of the rect

    SDL_RenderCopy(m_renderer, pText, NULL, &rect); // render

    SDL_FreeSurface(pSurfaceText); // free surface 
    SDL_DestroyTexture(pText); // destroy texture

}

void RenderWindow::clear(){
    SDL_RenderClear( m_renderer );
}

void RenderWindow::update(){
    SDL_RenderPresent( m_renderer );
}

RenderWindow::~RenderWindow(){
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_screen );

    m_renderer = nullptr;
    m_screen = nullptr;
}