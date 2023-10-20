#include "vector2f.h"

void Vector2f::normalize(){            // normalize vector 
	float magnitude = sqrt(x*x+y*y);
	if(magnitude > 0) {
		x /= magnitude;
		y /= magnitude;
	}
}

float Vector2f::getAngle(){             // returns angle in degrees from x and y
	return atan2( -x , y ) * ( 180 / M_PI );
}