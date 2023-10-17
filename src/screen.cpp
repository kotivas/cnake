/* Screen
is responsible for show window and render
*/


#include "screen.h"

Screen::Screen(const char* TITLE, const unsigned short SCREEN_WIDTH, const unsigned short SCREEN_LENGHT)
: m_screen(nullptr),m_render(nullptr)
{
    m_screen = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_LENGHT, SDL_WINDOW_SHOWN);

	if (m_screen == nullptr){
		std::cout << "screen failed to init. Error: " << SDL_GetError() << std::endl;
	}

	m_render = SDL_CreateRenderer(m_screen, -1, SDL_RENDERER_ACCELERATED);
    if (m_render == nullptr){
        std::cout << "Render failed to init. Error: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture* Screen::loadTexture(const char* path){
    SDL_Texture* texture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load( path );

    if ( loadedSurface == nullptr ){
        std::cout << IMG_GetError() << std::endl;
    } else {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( m_render, loadedSurface );
        if ( texture == nullptr ){
            std::cout << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return texture;
}

void Screen::render(SDL_Texture* texture, int x, int y, int w, int h, int angle){
	SDL_Rect src; 
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;//src.w;
	dst.h = h;//src.h;

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    //SDL_RenderCopy( m_render, texture, &src, &dst); // without angle, center & flip
    SDL_RenderCopyEx( m_render, texture, &src, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Screen::clear(){
    SDL_RenderClear( m_render );
}

void Screen::update(){
    SDL_RenderPresent( m_render );
}

// SDL_screen* Screen::getscreen() const{
//     return m_screen;
// }
// SDL_Renderer* Screen::getRender() const{
//     return m_render;
// }

Screen::~Screen(){
    SDL_DestroyRenderer( m_render );
    SDL_DestroyWindow( m_screen );

    m_render = nullptr;
    m_render = nullptr;
}