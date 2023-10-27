#include "math.h"
#pragma once

struct Vector2f {

	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}
	
	// returns float angle in degrees from x and y
	inline float getAngle(){
		return atan2( -x , y ) * ( 180 / M_PI );
	}

	float x, y;
};