#pragma once
#include <SDL.h>
#include "vector2f.h"

struct SnakeSegment {
	SnakeSegment()
	: angle{0.f}
	{}

	Vector2f 		position;
	SDL_Texture* 	texture;
	float 			angle;
	Vector2f 		direction;

	Vector2f 		buffdirection;

};