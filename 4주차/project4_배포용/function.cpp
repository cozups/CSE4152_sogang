#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	return x*x - 4*x + 4 -log(x);
}

double _fp1(double x) {
	return 2*x - 4 - (1/x);
}

double _f2(double x) {
	return x + 1 - 2*sin(x*M_PI);
}

double _fp2(double x) {
	return 1 - 2*M_PI*cos(x*M_PI);
}

double _f3(double x) {
	return x*x*x*x - 11*x*x*x + 42.35*x*x - 66.55*x + 35.1384;
}

double _fp3(double x) {
	return 4*x*x*x - 33*x*x + 42.35*2*x - 66.55;
}

double _f_sqrt(double x) {
	return x * x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0 * x;
}

double _f_vehicle(double x) {
	x = x * M_PI / 180;
	int l = 89, h = 49, D = 55;
	double b1 = 11.5 * M_PI / 180; // radian

	double A = l * sin(b1);
	double B = l * cos(b1);
	double C = (h + 0.5 * D) * sin(b1) - 0.5 * D * tan(b1);
	double E = (h + 0.5 * D) * cos(b1) - 0.5 * D;

	return A * sin(x) * cos(x) + B * sin(x) * sin(x) - C * cos(x) - E * sin(x);
}

double _fp_vehicle(double x) {
	x = x * M_PI / 180;
	int l = 89, h = 49, D = 55;
	double b1 = 11.5 * M_PI / 180; // radian

	double A = l * sin(b1);
	double B = l * cos(b1);
	double C = (h + 0.5 * D) * sin(b1) - 0.5 * D * tan(b1);
	double E = (h + 0.5 * D) * cos(b1) - 0.5 * D;

	return A * (cos(x) * cos(x) - sin(x) * sin(x)) + 2 * B * sin(x) * cos(x) + C * sin(x) - E * cos(x);
}

double _f_comp(double x) {
	return log(x)-1;
}

double _fp_comp(double x) {
	return 1/x;
}
