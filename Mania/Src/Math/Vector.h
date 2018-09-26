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

struct Vector3f
{
	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f) :
		x(x),
		y(y),
		z(z)
	{}

	inline Vector3f operator+(const Vector3f& vec) const
	{
		return Vector3f(x + vec.x, y + vec.y, z + vec.z);
	}

	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };
};

struct Vector4f
{
	Vector4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) :
		x(x),
		y(y),
		z(z),
		w(w)
	{}

	inline Vector4f operator+(const Vector4f& vec) const
	{
		return Vector4f(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };
	union { float w; float a; };
};

