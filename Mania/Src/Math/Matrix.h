#pragma once

#include "../Core/Common.h"
#include "Vector.h"

struct Matrix3f
{
	Matrix3f(float a0, float a1, float a2,
		float b0, float b1, float b2,
		float c0, float c1, float c2)
	{
		values[0][0] = a0; values[0][1] = a1; values[0][2] = a2; 
		values[1][0] = b0; values[1][1] = b1; values[1][2] = b2; 
		values[2][0] = c0; values[2][1] = c1; values[2][2] = c2; 
	}

	Matrix3f() {}

	inline Matrix3f operator*(const Matrix3f& matrix) const
	{
		Matrix3f res;
		for (uint32 i = 0; i < 3; i++)
		{
			for (uint32 j = 0; j < 3; j++)
			{
				res[i][j] = 0.0f;
				for (uint32 k = 0; k < 3; k++)
				{
					res[i][j] += values[i][k] * matrix[k][j];
				}
			}
		}
		return res;
	}

	inline const float* operator[](uint32 index) const { return values[index]; }
	inline float* operator[](uint32 index) { return values[index]; }

	float values[3][3];
};

Matrix3f mat3_create_identity();
void mat3_set_identity(Matrix3f* pMatrix);

Matrix3f mat3_create_translation(const Vector2f& translation);
Matrix3f mat3_create_scale(const Vector2f& scale);
Matrix3f mat3_create_rotation(float deg);

Matrix3f mat3_create_transform(const Vector2f& translation, const Vector2f& scale, float rotation);

struct Matrix4f
{
	Matrix4f(float a0, float a1, float a2, float a3,
		float b0, float b1, float b2, float b3,
		float c0, float c1, float c2, float c3,
		float d0, float d1, float d2, float d3)
	{
		values[0][0] = a0; values[0][1] = a1; values[0][2] = a2; values[0][3] = a3;
		values[1][0] = b0; values[1][1] = b1; values[1][2] = b2; values[1][3] = b3;
		values[2][0] = c0; values[2][1] = c1; values[2][2] = c2; values[2][3] = c3;
		values[3][0] = d0; values[3][1] = d1; values[3][2] = d2; values[3][3] = d3;
	}

	Matrix4f() {}

	inline const float* operator[](uint32 index) const { return values[index]; }
	inline float* operator[](uint32 index)  { return values[index]; }

	float values[4][4];
};

Matrix4f mat4_create_identity();
void mat4_set_identity(Matrix4f* pMatrix);

Matrix4f mat4_create_orthographic(float left, float right, float top, float bottom, float near, float far);
void mat4_set_orthographic(Matrix4f* pMatrix, float left, float right, float top, float bottom, float near, float far);
