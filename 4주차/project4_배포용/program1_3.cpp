#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp)
{
	double a0, b0, x0, x1 , temp;
	int n = 0;
	bool error = 0;

	fprintf(fp, " n                xn1                       |f(xn1)|\n");
	printf("Enter the initial guess a0, b0 : ");
	scanf("%lf %lf", &a0, &b0);

	
	while(1){
		x1 = (a0 + b0) / 2;
		fprintf(fp, "%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
		if (fabs(_f(x1)) < DELTA) {
			break;
		}
		if (_f(a0) * _f(x1) < 0) {
			b0 = x1;
		}
		else if (_f(b0) * _f(x1) < 0) {
			a0 = x1;
		}
		else {
			printf("There is no root on [%lf, %lf]\n", a0, b0);
			error = 1;
			break;
		}
		
		n++;
	}
	if (error) {
		fprintf(fp, "Root finding failed!\n");
	}
	else {
		printf(" n              xn1               |f(xn1)|\n");
		printf("------------------------------------------\n");
		printf("%2d  %20.15e  %12.15e\n", n, x1, fabs(_f(x1)));
	}
	
}