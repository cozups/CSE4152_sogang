#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define MY_RAND_MAX 32767
static unsigned long int next = 10;

int rand(void) {
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % (MY_RAND_MAX + 1);
}
void srand(unsigned int seed) {
	next = seed;
}

double _f(double* x, double* y, double* F, double xn, int num, double u) {
	int idx = -1;
	double res = 0;
	for (int i = 0; i <= num; i++) {
		if (xn < x[i]) {
			idx = i - 1;
			break;
		}
	}
	if (idx == -1) {
		idx = num - 2;
	}

	res = F[idx] + (y[idx] + (y[idx + 1] - y[idx]) / (x[idx + 1] - x[idx]) * (xn - x[idx]) / 2) * (xn - x[idx]) - u;
	return res;
}
void program2_2()
{
	FILE* fp_r, *fp_w;
	double *x, *y, *F;
	int num, nr;
	double gap;
	double u;
	srand(time(NULL));
	
	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	if (fp_r == NULL || fp_w == NULL) {
		printf("file open error!\n");
		return;
	}

	/***************************************************/
	/* file reading */
	fscanf(fp_r, "%d %lf", &num, &gap);
	x = new double[(num + 1)];
	y = new double[(num + 1)];
	F = new double[(num + 1)];
	for (int i = 0; i < num; i++) {
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}

	F[0] = 0;
	/* get cdf */
	for (int i = 1; i <= num; i++) {
		F[i] = F[i - 1] + (y[i - 1] + y[i]) * gap / 2;
	}

	/* input */
	printf("Enter the number of random number: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);
	
	while (nr--) {
		u = rand();
		u /= MY_RAND_MAX;
		int n = 0; // loop count
		double a = 0, b = 1;

		while (1) {
			double xn = (a + b) / 2;
			if (fabs(_f(x, y, F, xn, num, u)) < DELTA || n > Nmax || fabs(b-a) < EPSILON) {
				fprintf(fp_w, "%12.15lf\n", xn);
				break;
			}

			if (_f(x, y, F, a, num, u) * _f(x, y, F, xn, num, u) < 0) {
				b = xn;
			}
			else if (_f(x, y, F, b, num, u) * _f(x, y, F, xn, num, u) < 0) {
				a = xn;
			}
			n++;
		}
	}
	delete[] x;
	delete[] y;
	delete[] F;

	
	

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
