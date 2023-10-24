#pragma once
#include <SDL2/SDL.h>
#include "vector2f.h"

struct SnakeSegment {
	SnakeSegment()
	: position{0.0f, 0.0f}, pNext(nullptr),
	angle{0}, direction{0.0f, 0.0f}
	{}

	Vector2f 		position;
    SnakeSegment* 	pNext;
	SDL_Texture* 	texture;
	float 			angle;
	Vector2f 		direction;

	Vector2f 		buffdirection;
};