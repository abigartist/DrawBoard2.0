#include "calculate.h"

bool IsInLineRange(double x0,double y0,double x1,double y1,double x2,double y2) {
	double k = (y2 - y1) / (x2 - x1);
	double b = y2 - k * x2;
	double d = fabs(k * x0 + b - y0) / sqrt(pow(k, 2) + 1);
	return d < 10 ? YES : NO;
}

bool IsInRectRange(int x0, int y0, int x1, int y1, int x2, int y2) {
	if (x0 <= max(x1, x2) && x0 >= min(x1, x2) && y0 <= max(y1, y2) && y0 >= min(y1, y2)) {
		return YES;
	}
	return NO;
}

bool IsInCirRange(int x0, int y0, int x1, int y1, int x2, int y2) {
	if ((pow(x0 - x1, 2) + pow(y0 - y1, 2)) < (pow(x2 - x1, 2) + pow(y2 - y1, 2))) {
		return YES;
	}
	return NO;
}
/*

*/