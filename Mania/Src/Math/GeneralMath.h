#pragma once
#include <iostream>
#include <cmath>
#include "../Core/Common.h"

#define MATH_PI			3.14159265358979323846
#define MATH_E			2.71828182845904523536
#define MATH_SQRT2		1.41421356237309504880

#define MATH_DEG_TO_RAD(deg) (MATH_PI / 180.0) * deg
#define MATH_RAD_TO_DEG(rad) (180.0 / MATH_PI) * rad

#define MATH_MIN(n1, n2) n1 <= n2 ? n1 : n2
#define MATH_MAX(n1, n2) n1 >= n2 ? n1 : n2
#define MATH_CLAMP(x, upper, lower) MATH_MIN(upper, MATH_MAX(lower, x))

#define MATH_LERP(a, b, c)  a + c * (b - a)

