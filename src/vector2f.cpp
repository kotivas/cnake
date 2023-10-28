#include "vector2f.h"
#include <cmath>

// returns float angle in degrees from x and y
float Vector2f::getAngle(){
	return atan2( -x , y ) * ( 180 / M_PI );
}

// normalization of a vector
void Vector2f::normalize(){
	float magnitude = sqrt(x*x+y*y);
	if(magnitude > 0) {
		x /= magnitude;
		y /= magnitude;
	}
}

bool Vector2f::operator ==(const Vector2f& c) const{
	return (c.x == x && y == c.y);
}

bool Vector2f::operator !=(const Vector2f& c) const{
	return (c.x != x && y != c.y);
}