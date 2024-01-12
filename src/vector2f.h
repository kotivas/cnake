#pragma once

struct Vector2f {

	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	float 		getAngle(){	return atan2( -x , y ) * ( 180 / M_PI ); }

	bool 		operator==(const Vector2f& rhs) const { return (rhs.x == this->x && this->y == rhs.y); }
	bool 		operator!=(const Vector2f& rhs) const { return (rhs.x != this->x && this->y != rhs.y); }

	float 		x;
	float 		y;
};

// // normalization of a vector
// void Vector2f::normalize(){
// 	float magnitude = sqrt(x*x+y*y);
// 	if(magnitude > 0) {
// 		x /= magnitude;
// 		y /= magnitude;
// 	}
// }
