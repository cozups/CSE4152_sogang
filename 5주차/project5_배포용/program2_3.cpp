#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define MY_RAND_MAX 32767
static unsigned long int next = 10;

int hw_rand(void) {
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % (MY_RAND_MAX + 1);
}
void hw_srand(unsigned int seed) {
	next = seed;
}
void hw2_1() {
	/* homework 2-1 */
	int nr, num;
	double u;
	hw_srand(time(NULL));

	printf("\n----------- Homework 2_1 -----------\n");
	for (int i = 0; i < 3; i++) {
		double lambda = 0;
		nr = 100;
		num = nr;
		printf("Enter the lambda: ");
		scanf("%lf", &lambda);
		printf("%d\n", nr);

		double sum = 0, sqsum = 0;
		while (nr--) {
			u = hw_rand();
			u /= (MY_RAND_MAX + 1);

			double res = -1 * (log(1 - u) / lambda);
			printf("%12.15lf\n", res);
			sum += res;
			sqsum += res * res;
		}
		double avg = sum / num;
		printf("       avg         original avg        diff\n");
		printf("-------------------------------------------\n");
		printf("%12.15lf %12.15lf %12.15lf\n", avg, 1 / lambda, fabs(avg - (1 / lambda)));
		double var = (sqsum / num) - (avg * avg);
		printf("       var         original var        diff\n");
		printf("-------------------------------------------\n");
		printf("%12.15lf %12.15lf %12.15lf\n", var, 1 / (lambda * lambda), fabs(var - (1 / (lambda * lambda))));
	}
}

// HOMEWORK
void program2_3()
{
	FILE* fp_pdf, * fp_rand, * fp_hist;
	double gap;
	int num, rnum;
	fp_pdf = fopen("pdf_table.txt", "r");
	fp_rand = fopen("random_event_table.txt", "r");
	fp_hist = fopen("histogram.txt", "w");

	if (fp_pdf == NULL || fp_rand == NULL || fp_hist == NULL) {
		printf("file open error!\n");
		return;
	}

	/* file reading */
	fscanf(fp_pdf, "%d %lf", &num, &gap);
	double* x = new double[num];
	double* y = new double[num];

	for (int i = 0; i < num; i++) {
		fscanf(fp_pdf, "%lf %lf", &x[i], &y[i]);
	}

	fscanf(fp_rand, "%d", &rnum);
	double* r = new double[rnum];
	for (int i = 0; i < rnum; i++) {
		fscanf(fp_rand, "%lf", &r[i]);
	}
	
	/* sort r */
	for (int i = 0; i < rnum; i++) {
		for (int j = 0; j < rnum - i - 1; j++) {
			if (r[j + 1] < r[j]) {
				double tmp = r[j];
				r[j] = r[j + 1];
				r[j + 1] = tmp;
			}
		}
	}

	/* get historgram */
	double interval = x[1] - x[0];
	double start = x[0];
	int idx = 0;
	int *count = new int[num];
	memset(count, 0, num * sizeof(int));

	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < rnum; j++) {
			if (r[j] >= start && r[j] < start + interval) {
				count[i]++;
			}
		}
		start += interval;
	}

	start = x[0];
	fprintf(fp_hist, "Histogram\n");
	for (int i = 0; i < num - 1; i++) {
		fprintf(fp_hist, "[%lf, %lf]: %3d        ", start, start + interval, count[i]);
		for (int j = 0; j < count[i]; j++) {
			fprintf(fp_hist, "*");
		}
		fprintf(fp_hist, "\n");
		start += interval;
	}

	delete[] x;
	delete[] y;
	delete[] r;

	if (fp_pdf != NULL) fclose(fp_pdf);
	if (fp_rand != NULL) fclose(fp_rand);
	if (fp_hist != NULL) fclose(fp_hist);

}

double _f_hw(double* x, double* y, double* F, double xn, int num, double u) {
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
double _fp_hw(double* x, double* y, double* F, double xn, int num, double u) {
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

	double s = (xn - x[idx]) / (x[idx + 1] - x[idx]);

	res = (1 - s) * y[idx] + s * y[idx + 1];
	return res;
}

// HOMEWORK
void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;
	FILE* fp_r, * fp_w;
	double* x, * y, * F, *root;
	int num, nr;
	double gap;
	double u;
	hw_srand(time(NULL));

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	if (fp_r == NULL || fp_w == NULL) {
		printf("file open error!\n");
		return;
	}

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
	printf("\n----------- Homework 2-2(a) -----------\n");
	printf("Enter the number of random number: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);
	root = new double[nr];


	CHECK_TIME_START;

	// something to do...
	for (int i = 0; i < nr; i++) {
		u = hw_rand();
		u /= MY_RAND_MAX;
		int n = 0; // loop count
		double a = 0, b = 1;

		while (1) {
			double xn = (a + b) / 2;
			if (fabs(_f_hw(x, y, F, xn, num, u)) < DELTA || n > Nmax || fabs(b - a) < EPSILON) {
				root[i] = xn;
				break;
			}

			if (_f_hw(x, y, F, a, num, u) * _f_hw(x, y, F, xn, num, u) < 0) {
				b = xn;
			}
			else if (_f_hw(x, y, F, b, num, u) * _f_hw(x, y, F, xn, num, u) < 0) {
				a = xn;
			}
			n++;
		}
	}

	CHECK_TIME_END(resultTime);

	for (int i = 0; i < nr; i++) {
		fprintf(fp_w, "%12.15lf\n", root[i]);
	}

	delete[] x;
	delete[] y;
	delete[] F;
	delete[] root;

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
	
}

void program2_2_b()
{
	__int64 start, freq, end;
	float resultTime = 0;
	FILE* fp_r, * fp_w;
	double* x, * y, * F, * root;
	int num, nr;
	double gap;
	double u;
	hw_srand(time(NULL));

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	if (fp_r == NULL || fp_w == NULL) {
		printf("file open error!\n");
		return;
	}

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
	printf("\n----------- Homework 2-2(b) -----------\n");
	printf("Enter the number of random number: ");
	scanf("%d", &nr);
	fprintf(fp_w, "%d\n", nr);
	root = new double[nr];

	CHECK_TIME_START;

	// something to do...
	for (int i = 0; i < nr; i++) {
		u = hw_rand();
		u /= MY_RAND_MAX;
		int n = 0; // loop count
		double a = 0, b = 1;
		double xn;

		/* Bisection */
		while (1) {
			xn = (a + b) / 2;
			if (fabs(_f_hw(x, y, F, xn, num, u)) < 0.000001 || fabs(b - a) < 0.000001) {
				break;
			}

			if (_f_hw(x, y, F, a, num, u) * _f_hw(x, y, F, xn, num, u) < 0) {
				b = xn;
			}
			else if (_f_hw(x, y, F, b, num, u) * _f_hw(x, y, F, xn, num, u) < 0) {
				a = xn;
			}
			n++;
		}

		
		// Secant 
		double x0 = a, x1 = b;
		while (1) {
			double temp = x1 - _f_hw(x, y, F, x1, num, u) * (x1 - x0) / (_f_hw(x, y, F, x1, num, u) - _f_hw(x, y, F, x0, num, u));
			n++;
			x0 = x1; x1 = temp;
			if (fabs(_f_hw(x, y, F, x1, num, u)) < DELTA || n > Nmax || fabs(x1 - x0) < EPSILON) {
				root[i] = x1;
				break;
			}
		}

		/*
		// Newton-Raphson
		double n0 = a, n1;
		while (1) {
			n1 = n0 - (_f_hw(x, y, F, n0, num, u) / _fp_hw(x, y, F, n0, num, u));
			n++;
			if (fabs(_f_hw(x, y, F, n1, num, u)) < DELTA || n > Nmax || fabs(n1 - n0) < EPSILON) {
				root[i] = n1;
				break;
			}
			n0 = n1;
		}*/

	}
	CHECK_TIME_END(resultTime);

	for (int i = 0; i < nr; i++) {
		fprintf(fp_w, "%12.15lf\n", root[i]);
	}

	delete[] x;
	delete[] y;
	delete[] F;
	delete[] root;

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}