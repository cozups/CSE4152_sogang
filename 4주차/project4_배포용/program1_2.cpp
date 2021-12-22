#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1, temp;
	int n = 0;

	if (fp == NULL)
		return;

	fprintf(fp, " n                xn1                       |f(xn1)|\n");
	printf("Enter the initial guess x0, x1: ");
	scanf("%lf %lf", &x0, &x1);

	while (1) {
		fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
		temp = x1 - _f(x1) * (x1 - x0) / (_f(x1) - _f(x0));
		n++;
		x0 = x1;
		x1 = temp;
		if (fabs(_f(x1)) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON) {
			break;
		}
	}
	fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
	printf(" n              xn1               |f(xn1)|\n");
	printf("------------------------------------------\n");
	printf("%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
}
