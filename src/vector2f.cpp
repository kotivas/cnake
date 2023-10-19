#include "vector2f.h"

void Vector2f::normalize(){
	float magnitude = sqrt(x*x+y*y);
	if(magnitude > 0) {
		x /= magnitude;
		y /= magnitude;
	}
}

float Vector2f::getAngle(){

	// ебучая формула для нахождения угла

	return 0.f;
}