#pragma once

struct Vector2f
{
	Vector2f(float x = 0.0f, float y = 0.0f) :
		x(x),
		y(y)
	{}

	inline Vector2f operator+(const Vector2f& vec) const
	{
		return Vector2f(x + vec.x, y + vec.y);
	}

	float x;
	float y;
};
