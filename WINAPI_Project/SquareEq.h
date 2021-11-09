#pragma once
#include <Windows.h>
#include <math.h>

FLOAT CalcDiscriminant(FLOAT a, FLOAT b, FLOAT c) {
	return pow(b, 2.0) - 4.0 * a * c;
}

FLOAT* CalcSquareEq(FLOAT a, FLOAT b, FLOAT c)
{
	FLOAT D = CalcDiscriminant(a, b, c);
	if (a != 0.0) {
		if (D > 0.0)
		{
			FLOAT* result = calloc(2, sizeof(FLOAT));
			result[0] = (-b + sqrt(D)) / (2.0 * a);
			result[1] = (-b - sqrt(D)) / (2.0 * a);
			return result;
		}
		if (D == 0.0)
		{
			FLOAT* result = calloc(2, sizeof(FLOAT));
			result[0] = (-b) / (2.0 * a);
			result[1] = (-b) / (2.0 * a);
			return result;
		}
		else
		{
			FLOAT* result = calloc(2, sizeof(FLOAT));
			result[0] = 0.0;
			result[1] = 0.0;
			return result;
		}
	}
	else
	{
		FLOAT* result = calloc(2, sizeof(FLOAT));
		result[0] = 0.0;
		result[1] = 0.0;
		return result;
	}
}