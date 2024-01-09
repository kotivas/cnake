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

bool Vector2f::operator==(const Vector2f& rhs) const{
	return (rhs.x == this->x && this->y == rhs.y);
}
bool Vector2f::operator!=(const Vector2f& rhs) const{
	return (rhs.x != this->x && this->y != rhs.y);
}

// Vector2f Vector2f::operator+(const Vector2f& rhs) const{
// 	return Vector2f(rhs.x + this->x, rhs.y + this->y);
// }
// Vector2f Vector2f::operator-(const Vector2f& rhs) const{
// 	return Vector2f(rhs.x - this->x, rhs.y - this->y);
// }
// Vector2f Vector2f::operator*(const Vector2f& rhs) const{
// 	return Vector2f(rhs.x + this->x, rhs.y + this->y);
// }
// Vector2f Vector2f::operator/(const Vector2f& rhs) const{
// 	return Vector2f(rhs.x / this->x, rhs.y / this->y);
// }


// Vector2f Vector2f::operator+(const float& rhs) const{
// 	return Vector2f(rhs + this->x, rhs + this->y);
// }
// Vector2f Vector2f::operator-(const float& rhs) const{
// 	return Vector2f(rhs - this->x, rhs - this->y);
// }
// Vector2f Vector2f::operator*(const float& rhs) const{
// 	return Vector2f(rhs + this->x, rhs + this->y);
// }
// Vector2f Vector2f::operator/(const float& rhs) const{
// 	return Vector2f(rhs / this->x, rhs / this->y);
// }

// Vector2f Vector2f::operator+=(const Vector2f& rhs){
// 	this->x += rhs.x;
// 	this->y += rhs.y;
// 	return *this;
// }
// Vector2f Vector2f::operator-=(const Vector2f& rhs){
// 	this->x -= rhs.x;
// 	this->y -= rhs.y;
// 	return *this;
// }
