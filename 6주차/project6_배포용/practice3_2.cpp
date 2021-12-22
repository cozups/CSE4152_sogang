#include "my_solver.h"

void mult_imag(int degree, double a, double b, double* real, double* imag, double coef) {
	// (a+bi) * (a+bi)
	*real = a; *imag = b;
	for (int i = 0; i < degree; i++) {
		double x = *real, y = *imag;
		*real = x * a - y * b;
		*imag = a * y + b * x;
	}
	*real *= coef;
	*imag *= coef;
}

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;

	printf("\n--------------------------practice3_2--------------------------\n");

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/
		// read polynomial in file
		for (i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf", &poly[i]);
		}

		// solve polynomial
		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);

		// print result in file
		if (fail) {
			printf("ROOT FINDING FAILED\n");
			fprintf(fp_w, "ROOT FINDING FAILED\n");
		}
		else {
			printf("       REAL       IMAGINARY       |f(x*)|\n");
			fprintf(fp_w, "       REAL       IMAGINARY       |f(x*)|\n");
			for (i = 0; i < DEGREE; i++) {
				// calculate
				int j, d = DEGREE;
				double f = 0, f_r = 0, f_i = 0, real = 0, imag = 0;
				for (j = 0; j < NCOEF; j++) {
					mult_imag(DEGREE - j, zeror[i], zeroi[i], &real, &imag, poly[j]);
					f_r += real; f_i += imag;
				}
				f = fabs(sqrt(f_r * f_r + f_i * f_i));

				printf("[%d] %12lf %12lf %12lf\n", (i + 1), zeror[i], zeroi[i], f);
				fprintf(fp_w, "[%d] %12lf %12lf %12lf\n", (i + 1), zeror[i], zeroi[i], f);
			}
		}
		printf("\n");

		/********************************/


		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}