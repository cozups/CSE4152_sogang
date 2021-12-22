#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

double p[SOLNUMS][3];
double tt[SOLNUMS];
double tr[SOLNUMS];
double C, b;

void fcnhw3_1(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		
		for (int i = 0; i < 4; i++) {
			fvec[i] = (x[0] - p[i][0]) * (x[0] - p[i][0]) + (x[1] - p[i][1]) * (x[1] - p[i][1]) +
				(x[2] - p[i][2]) * (x[2] - p[i][2]) - (C * (tr[i] + x[3] - tt[i])) * (C * (tr[i] + x[3] - tt[i]));
		}

		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/

		fjac[0] = 2 * (x[0] - p[0][0]);		fjac[4] = 2 * (x[1] - p[0][1]);		fjac[8] = 2 * (x[2] - p[0][2]);		fjac[12] = -2 * C * C * (tr[0] + x[3] - tt[0]);
		fjac[1] = 2 * (x[0] - p[1][0]);		fjac[5] = 2 * (x[1] - p[1][1]);		fjac[9] = 2 * (x[2] - p[1][2]);		fjac[13] = -2 * C * C * (tr[1] + x[3] - tt[1]);
		fjac[2] = 2 * (x[0] - p[2][0]);		fjac[6] = 2 * (x[1] - p[2][1]);		fjac[10] = 2 * (x[2] - p[2][2]);	fjac[14] = -2 * C * C * (tr[2] + x[3] - tt[2]);
		fjac[3] = 2 * (x[0] - p[3][0]);		fjac[7] = 2 * (x[1] - p[3][1]);		fjac[11] = 2 * (x[2] - p[3][2]);	fjac[15] = -2 * C * C * (tr[3] + x[3] - tt[3]);

		/********************************/
	}
}

void fcnhw3_2(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	for (int i = 0; i < 4; i++) {
		fvec[i] = (x[0] - p[i][0]) * (x[0] - p[i][0]) + (x[1] - p[i][1]) * (x[1] - p[i][1]) +
			(x[2] - p[i][2]) * (x[2] - p[i][2]) - (C * (tr[i] + x[3] - tt[i])) * (C * (tr[i] + x[3] - tt[i]));
	}

	/********************************/
}

void program3_1() {
	char readfile[256];
	char writefile[256];

	int n = SOLNUMS;
	double x[SOLNUMS];	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
	double tmp[3];

	printf("\n--------------------------program3_1--------------------------\n");

	for (int t = 0; t <= 2; t++) {

		sprintf(readfile, "GPS_signal_%d.txt", t);
		sprintf(writefile, "GPS_position_3-1_%d.txt", t);

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

		fscanf(fp_r, "%lf %lf", &C, &b);
		printf("초기값 x1, x2, x3을 입력하세요: ");
		scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);
		x[3] = b;
		tmp[0] = x[0]; tmp[1] = x[1]; tmp[2] = x[2];

		// HYBRJ1
		printf("By HYBRJ1\n");
		printf("초기값1: x(0) = {%lf, %lf, %lf, %lf}\n\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_w, "초기값1: x(0) = {%lf, %lf, %lf, %lf}\n\n", x[0], x[1], x[2], x[3]);

		for (int i = 0; i < SOLNUMS; i++) {
			fscanf(fp_r, "%lf %lf %lf %lf %lf", &p[i][0], &p[i][1], &p[i][2], &tt[i], &tr[i]);
		}

		hybrj1_(fcnhw3_1, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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
		printf("|f4(x*)| = %12lf\n\n", fabs(fvec[3]));

		fprintf(fp_w, "|f1(x*)| = %12lf\n", fabs(fvec[0]));
		fprintf(fp_w, "|f2(x*)| = %12lf\n", fabs(fvec[1]));
		fprintf(fp_w, "|f3(x*)| = %12lf\n", fabs(fvec[2]));
		fprintf(fp_w, "|f3(x*)| = %12lf\n\n", fabs(fvec[3]));

		
		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);

		double wa2[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
		int lwa2 = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

		sprintf(writefile, "GPS_position_3-2_%d.txt", t);
		fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		// HYBRD1
		x[0] = tmp[0]; x[1] = tmp[1]; x[2] = tmp[2]; x[3] = b;
		printf("By HYBRD1\n");
		printf("초기값1: x(0) = {%lf, %lf, %lf, %lf}\n\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_w, "초기값1: x(0) = {%lf, %lf, %lf, %lf}\n\n", x[0], x[1], x[2], x[3]);

		hybrd1_(fcnhw3_2, &n, x, fvec, &tol, &info, wa2, &lwa2);

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
		printf("|f4(x*)| = %12lf\n\n", fabs(fvec[3]));

		fprintf(fp_w, "|f1(x*)| = %12lf\n", fabs(fvec[0]));
		fprintf(fp_w, "|f2(x*)| = %12lf\n", fabs(fvec[1]));
		fprintf(fp_w, "|f3(x*)| = %12lf\n", fabs(fvec[2]));
		fprintf(fp_w, "|f3(x*)| = %12lf\n\n", fabs(fvec[3]));

		/********************************/

		if (fp_w != NULL) fclose(fp_w);
	}


}