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

	bool 		operator==(const Vector2f& rhs) const;
	bool 		operator!=(const Vector2f& rhs) const;

	// Vector2f    operator+(const Vector2f& rhs) const;
	// Vector2f    operator-(const Vector2f& rhs) const;
	// Vector2f    operator*(const Vector2f& rhs) const;
	// Vector2f    operator/(const Vector2f& rhs) const;

	// Vector2f    operator+(const float& rhs) const;
	// Vector2f    operator-(const float& rhs) const;
	// Vector2f    operator*(const float& rhs) const;
	// Vector2f    operator/(const float& rhs) const;


	// Vector2f    operator+=(const Vector2f& rhs);
	// Vector2f    operator-=(const Vector2f& rhs);

	float 		x;
	float 		y;
};