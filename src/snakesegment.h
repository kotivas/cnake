#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2f.h"

struct SnakeSegment {
	SnakeSegment(int i)
	:position{0.0f, 0.0f}, pNext(nullptr),
	angle{0}, direction{0.0f, 0.0f}, index(i)
	{}

	Vector2f position;
    SnakeSegment* pNext;
	SDL_Texture* texture;
	float angle;
	Vector2f direction;
	Hitbox hitbox;

	int index;
};