#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_3(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/

		fvec[0] = exp(2 * x[0]) - x[1] + 4.0;
		fvec[1] = x[1] - x[2] * x[2] - 1.0;
		fvec[2] = x[2] - sin(x[0]);

		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/

		fjac[0] = 2 * exp(2 * x[0]);	fjac[3] = -1;	fjac[6] = 0;
		fjac[1] = 0;					fjac[4] = 1;	fjac[7] = -2 * x[2];
		fjac[2] = -cos(x[0]);			fjac[5] = 0;	fjac[8] = 1;

		/********************************/
	}
}

void practice3_3(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;


	printf("\n--------------------------practice3_3--------------------------\n");

	FILE* fp_w = fopen("roots_3-3.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-3.txt");
		return;
	}

	/********************************/

	// ------------- �ʱⰪ1
	printf("�ʱⰪ1: x(0) = {0, 0, 0}\n\n");
	fprintf(fp_w, "�ʱⰪ1: x(0) = {0, 0, 0}\n\n");

	hybrj1_(fcn3_3, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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

	// -------------- �ʱⰪ2
	x[0] = 1.55; x[1] = 1.39; x[2] = 1.1;
	printf("�ʱⰪ2: x(0) = {1.55, 1.39, 1.10}\n\n");
	fprintf(fp_w, "�ʱⰪ2: x(0) = {1.55, 1.39, 1.10}\n\n");

	hybrj1_(fcn3_3, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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
