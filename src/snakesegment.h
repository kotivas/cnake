#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"

struct SnakeSegment {
	SnakeSegment()
	: pNext(nullptr), angle{0.f}
	{}

	Vector2f 		position;
    SnakeSegment* 	pNext;
	SDL_Texture* 	texture;
	float 			angle;
	Vector2f 		direction;

	Vector2f 		buffdirection;

};