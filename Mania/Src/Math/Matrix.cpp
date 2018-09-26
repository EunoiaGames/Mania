#include "Matrix.h"
#include "GeneralMath.h"

Matrix3f mat3_create_identity()
{
	return Matrix3f();
}

void mat3_set_identity(Matrix3f * pMatrix)
{
}

Matrix3f mat3_create_translation(const Vector2f & translation)
{
	return Matrix3f(0.0f, 0.0f, translation.x,
			        0.0f, 0.0f, translation.y,
					0.0f, 0.0f, 1.0f);
}

Matrix3f mat3_create_scale(const Vector2f & scale)
{
	return Matrix3f(scale.x, 0.0f, 0.0f,
					0.0f, scale.y, 0.0f,
					0.0f, 0.0f, 1.0f);
}

Matrix3f mat3_create_rotation(float deg)
{
	float rad = MATH_DEG_TO_RAD(deg);
	float _cos = cos(-rad);
	float _sin = sin(-rad);

	return Matrix3f(_cos, -_sin, 0.0f,
					_sin, _cos, 0.0f,
					0.0f, 0.0f, 1.0f);
}

Matrix3f mat3_create_transform(const Vector2f & translation, const Vector2f & scale, float rotation)
{
	return mat3_create_translation(translation) * (mat3_create_rotation(rotation) * mat3_create_scale(scale));
}


Matrix4f mat4_create_identity()
{
	return Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

void mat4_set_identity(Matrix4f * pMatrix)
{
	for (uint32 i = 0; i < 4; i++)
		for (uint32 j = 0; j < 4; j++)
			pMatrix->values[i][j] = i == j ? 1.0f : 0.0f;
}

Matrix4f mat4_create_orthographic(float left, float right, float top, float bottom, float near, float far)
{
	Matrix4f matrix;
	mat4_set_orthographic(&matrix, left, right, top, bottom, near, far);
	return matrix;
}

void mat4_set_orthographic(Matrix4f* pMatrix, float left, float right, float top, float bottom, float near, float far)
{
	pMatrix->values[0][0] = 2.0f / (right - left); pMatrix->values[0][1] = float(0);					  pMatrix->values[0][2] = float(0);					pMatrix->values[0][3] = -((right + left) / (right - left));
	pMatrix->values[1][0] = float(0);				   pMatrix->values[1][1] = 2.0f / (top - bottom);	  pMatrix->values[1][2] = float(0);					pMatrix->values[1][3] = -((top + bottom) / (top - bottom));
	pMatrix->values[2][0] = float(0);				   pMatrix->values[2][1] = float(0);					  pMatrix->values[2][2] = -2.0f / (far - near); pMatrix->values[2][3] = -((far + near) / (far - near));
	pMatrix->values[3][0] = float(0);				   pMatrix->values[3][1] = float(0);					  pMatrix->values[3][2] = float(0);					pMatrix->values[3][3] = float(1);
}
