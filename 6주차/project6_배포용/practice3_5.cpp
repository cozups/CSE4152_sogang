#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_5(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = 10 * x[0] - 2 * x[1] * x[1] + x[1] - 2 * x[2] - 5;
	fvec[1] = 8 * x[1] * x[1] + 4 * x[2] * x[2] - 9;
	fvec[2] = 8 * x[1] * x[2] + 4;

	/********************************/
}

void practice3_5(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 1.0, -1.0, 1.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	printf("\n--------------------------practice3_5--------------------------\n");

	FILE* fp_w = fopen("roots_3-5.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/

	// ---------- 초기값1
	printf("초기값: x(0) = {1.0, -1.0, 1.0}\n\n");
	fprintf(fp_w, "초기값: x(0) = {1.0, -1.0, 1.0}\n\n");

	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);

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

	printf("|f1(x*)| = %12lf\n", fabs(fvec[0]));
	printf("|f2(x*)| = %12lf\n", fabs(fvec[1]));
	printf("|f3(x*)| = %12lf\n\n", fabs(fvec[2]));

	fprintf(fp_w, "|f1(x*)| = %12lf\n", fabs(fvec[0]));
	fprintf(fp_w, "|f2(x*)| = %12lf\n", fabs(fvec[1]));
	fprintf(fp_w, "|f3(x*)| = %12lf\n\n", fabs(fvec[2]));

	// ---------- 초기값2
	x[0] = 1; x[1] = 1; x[2] = -1;
	printf("초기값: x(0) = {1.0, 1.0, -1.0}\n\n");
	fprintf(fp_w, "초기값: x(0) = {1.0, 1.0, -1.0}\n\n");

	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);

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

	printf("|f1(x*)| = %12lf\n", fabs(fvec[0]));
	printf("|f2(x*)| = %12lf\n", fabs(fvec[1]));
	printf("|f3(x*)| = %12lf\n", fabs(fvec[2]));

	fprintf(fp_w, "|f1(x*)| = %12lf\n", fabs(fvec[0]));
	fprintf(fp_w, "|f2(x*)| = %12lf\n", fabs(fvec[1]));
	fprintf(fp_w, "|f3(x*)| = %12lf\n", fabs(fvec[2]));

	/********************************/

	fclose(fp_w);
}