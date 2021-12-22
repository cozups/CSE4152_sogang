#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

//[0][1]
// x, y

void fcnpr3_3(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = (sin(x[0] * x[1] + M_PI / 6) + sqrt(x[0] * x[0] * x[1] * x[1] + 1)) / cos(x[0] - x[1]) + 2.8;
	fvec[1] = (x[0] * exp(x[0] * x[1] + M_PI / 6) - sin(x[0] - x[1])) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) - 1.66;

	/********************************/
}

void program3_3() {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 20.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	printf("\n--------------------------program3_3--------------------------\n");

	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-3.txt");
		return;
	}

	/********************************/
	printf("초기값1: x(0) = {%lf, %lf}\n\n", x[0], x[1]);
	fprintf(fp_w, "초기값1: x(0) = {%lf, %lf}\n\n", x[0], x[1]);

	hybrd1_(fcnpr3_3, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("Info: %d\n\n", info);
	fprintf(fp_w, "Info: %d\n\n", info);

	printf("root:\n");
	fprintf(fp_w, "root:\n");
	for (int i = 0; i < SOLNUMS; i++) {
		printf("%12lf ", x[i]);
		fprintf(fp_w, "%12lf ", x[i]);
	}
	printf("\n\n");
	fprintf(fp_w, "\n\n");

	for (int i = 0; i < SOLNUMS; i++) {
		printf("|f%d(x*)| = %12lf\n", i + 1, fabs(fvec[i]));
		fprintf(fp_w, "|f%d(x*)| = %12lf\n", i + 1, fabs(fvec[i]));
	}

	/********************************/

	fclose(fp_w);
}