#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_4(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/

		fvec[0] = x[0] + x[1] + x[2] - 3;
		fvec[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5;
		fvec[2] = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1;


		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/

		fjac[0] = 1;							fjac[3] = 1;			fjac[6] = 1;
		fjac[1] = 2 * x[0];						fjac[4] = 2 * x[1];		fjac[7] = 2 * x[2];
		fjac[2] = exp(x[0]) + x[1] - x[2];		fjac[5] = x[0];			fjac[8] = -x[0];


		/********************************/
	}
}

void practice3_4(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.1, 1.2, 2.5 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
	
	printf("\n--------------------------practice3_4--------------------------\n");

	FILE* fp_w = fopen("roots_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-4.txt");
		return;
	}

	/********************************/
	// ---------- �ʱⰪ1
	printf("�ʱⰪ: x(0) = {0.1, 1.2, 2.5}\n\n");
	fprintf(fp_w, "�ʱⰪ: x(0) = {0.1, 1.2, 2.5}\n\n");

	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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

	// ---------- �ʱⰪ2
	x[0] = 1; x[1] = 0; x[2] = 1;
	printf("�ʱⰪ: x(0) = {1.0, 0.0, 1.0}\n\n");
	fprintf(fp_w, "�ʱⰪ: x(0) = {1.0, 0.0, 1.0}\n\n");

	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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
