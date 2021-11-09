#include <stdio.h>
#include <math.h>

#define DEBUG
#define X1 0
#define Y1 0
#define X2 0
#define Y2 5
#define X3 5
#define Y3 0

#define square(value) (value*value)
#define getLineLenght(x_1, y_1, x_2, y_2) sqrt(square((x_2 - x_1))+square((y_2 - y_1)))

int isTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
double getTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3);
double getTrianglePerimeter(int x1, int y1, int x2, int y2, int x3, int y3);

int mainfunc() {
#ifdef DEBUG
#include <locale.h>
	setlocale(LC_ALL, "rus");
#if X1 == X2 && Y1 == Y2 || X2 == X3 && Y2 == Y3 || X1 == X3 && Y1 == Y3
	printf(" акие-то точки совпадают\n");
#else
	printf("“очки не совпадают, но все же могут лежать на одной пр€мой\n");
#endif
	printf("\n%d", square(X1));
	printf("\n%f", getLineLenght(X2, Y2, X3, Y3));
	printf("\n%d", isTriangle(X1, Y1, X2, Y2, X3, Y3));
	printf("\n%f", getTriangleArea(X1, Y1, X2, Y2, X3, Y3));
	printf("\n%f", getTrianglePerimeter(X1, Y1, X2, Y2, X3, Y3));
#else
	printf("Hello world!");
#endif

	return 0;
}

int isTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	double edgesLenght[] = { 1, 2, 3 };
	edgesLenght[0] = getLineLenght(x2, y2, x3, y3);
	edgesLenght[1] = getLineLenght(x1, y1, x2, y2);
	edgesLenght[2] = getLineLenght(x1, y1, x3, y3);

	double min = edgesLenght[0];
	for (int i = 0; i < 3; i++)
	{
		if (min > edgesLenght[i]) {
			double temp = edgesLenght[i];
			edgesLenght[i] = min;
			edgesLenght[i - 1] = temp;
			min = temp;
		}
	}

	if (edgesLenght[0] != 0 && edgesLenght[1] != 0 && edgesLenght[2] != 0) {
		if (edgesLenght[2] == edgesLenght[0] + edgesLenght[1])
			return 0;
		else
			return 1;
	}
	else
		return 0;
}

double getTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (isTriangle(x1, y1, x2, y2, x3, y3)) {
		double p = getTrianglePerimeter(x1, y1, x2, y2, x3, y3) / 2;
		return sqrt(p * (p * getLineLenght(x1, y1, x2, y2)) * (p - getLineLenght(x2, y2, x3, y3)) * (p - getLineLenght(x1, y1, x3, y3)));
	}
	else
		return 0;
}

double getTrianglePerimeter(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (isTriangle(x1, y1, x2, y2, x3, y3))
		return getLineLenght(x1, y1, x2, y2) + getLineLenght(x2, y2, x3, y3) + getLineLenght(x1, y1, x3, y3);
	else
		return 0;
}
