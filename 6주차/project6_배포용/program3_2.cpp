#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

//[0][1][2][3]
// w, x, y, z

void fcnpr3_2(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/

		fvec[0] = x[1] + 10 * x[2] + 9;
		fvec[1] = sqrt(5) * (x[3] - x[0]) - 2 * sqrt(5);
		fvec[2] = (x[2] - 2 * x[3]) * (x[2] - 2 * x[3]) - 9;
		fvec[3] = sqrt(10) * (x[1] - x[0]) * (x[1] - x[0]) - 2 * sqrt(10);

		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/

		fjac[0] = 0;									fjac[4] = 1;								fjac[8] = 10;
		fjac[1] = -sqrt(5);								fjac[5] = 0;								fjac[9] = 0;
		fjac[2] = 0;									fjac[6] = 0;								fjac[10] = 2 * (x[2] - 2 * x[3]);
		fjac[3] = 2 * sqrt(10) * (x[1] - x[0]) * -1;	fjac[7] = 2 * sqrt(10) * (x[1] - x[0]);		fjac[11] = 0;

		fjac[12] = 0;
		fjac[13] = sqrt(5);
		fjac[14] = 2 * (x[2] - 2 * x[3]) * -2;
		fjac[15] = 0;

		/********************************/
	}
}

void program3_2() {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.9,-0.9,1.25,-1.25 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	printf("\n--------------------------program3_2--------------------------\n");

	FILE* fp_w = fopen("roots_found_3-2.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-2.txt");
		return;
	}

	/********************************/
	printf("초기값1: x(0) = {%lf, %lf, %lf, %lf}\n\n", x[0], x[1], x[2], x[3]);
	fprintf(fp_w, "초기값1: x(0) = {%lf, %lf, %lf, %lf}\n\n", x[0], x[1], x[2], x[3]);

	hybrj1_(fcnpr3_2, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("Info: %d\n\n", info);
	fprintf(fp_w, "Info: %d\n\n", info);

	printf("root:\n");
	printf("       w            x            y            z\n");
	fprintf(fp_w, "root:\n");
	fprintf(fp_w, "       w            x            y            z\n");
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