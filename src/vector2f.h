#pragma once

struct Vector2f {

	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	float 		getAngle();
	void		normalize();

	bool 		operator==(const Vector2f& c) const;
	bool 		operator!=(const Vector2f& c) const;

	// Vector2f    operator+(const Vector2f& c) const;
	// Vector2f    operator-(const Vector2f& c) const;

	float 		x;
	float 		y;
};