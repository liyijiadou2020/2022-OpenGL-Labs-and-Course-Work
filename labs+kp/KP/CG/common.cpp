#include "common.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

void rotation2f(float* x, float* y, float degree)
{
	float angle = degree * M_PI / 180;

	float tmpX = *x * cos(angle) - *y * sin(angle);
	float tmpY = *y * cos(angle) + *x * sin(angle);

	*x = tmpX;
	*y = tmpY;
}

void common::rotation(float pos[3], float angle, float x, float y, float z)
{
	if (x == 1) {
		rotation2f(pos + 1, pos + 2, angle);
	} else if (y == 1) {
		rotation2f(pos, pos + 2, angle);
	} else {
		rotation2f(pos, pos + 1, angle);
	}
}
