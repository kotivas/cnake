#include "vector2f.h"

void Vector2f::normalize(){
	float mag = sqrt(x*x+y*y);
	if(mag > 0) {
		x /= mag;
		y /= mag;
	}
}
