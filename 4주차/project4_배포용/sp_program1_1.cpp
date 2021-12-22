#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float x0, x1;
	int n = 0;

	if (fp == NULL)
		return;

	fprintf(fp, " n                xn1                       |sp_f(xn1)|\n");
	printf("Enter the initial guess x0: ");
	scanf("%f", &x0);

	x1 = x0;
	while (1) {
		fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_sp_f(x1)));
		x1 = x0 - (_sp_f(x0) / _sp_fp(x0));
		n++;
		if (fabs(_sp_f(x1)) < DELTA || n >= Nmax || fabs(x1 - x0) < EPSILON) {
			break;
		}
		x0 = x1;
	}
	fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_sp_f(x1)));
	printf(" n              xn1               |sp_f(xn1)|\n");
	printf("------------------------------------------\n");
	printf("%2d  %20.15e  %12.15e\n", n, x1, fabs(_sp_f(x1)));
}
