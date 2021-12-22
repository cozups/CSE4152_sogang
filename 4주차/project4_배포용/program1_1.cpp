#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double x0, x1;
	int n = 0;

	if (fp == NULL)
		return;

	fprintf(fp, " n                xn1                       |f(xn1)|\n");
	printf("Enter the initial guess x0: ");
	scanf("%lf", &x0);

	x1 = x0;
	while (1) {
		fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
		x1 = x0 - (_f(x0) / _fp(x0));
		n++;
		if (fabs(_f(x1)) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON) {
			break;
		}
		x0 = x1;
	}
	fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
	printf(" n              xn1               |f(xn1)|\n");
	printf("------------------------------------------\n");
	printf("%2d  %20.15lf  %12.15lf\n", n, x1, fabs(_f(x1)));
}
