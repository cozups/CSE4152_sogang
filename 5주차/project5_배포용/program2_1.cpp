#include "my_solver.h"

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;
	double *x, *y;
	int num;
	double gap;
	double area = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/
	/* file reading */
	fscanf(fp_r, "%d %lf", &num, &gap);
	x = new double[num];
	y = new double[num];
	for (int i = 0; i < num; i++) {
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}

	/* 수치 적분(합성 사다리꼴) */
	area += y[0];
	for (int i = 1; i < num - 1; i++) {
		area += 2 * y[i];
	}
	area += y[num - 1];
	area = area / 2 * gap;

	/* normalization - f(x) */
	for (int i = 0; i < num; i++) {
		y[i] /= area;
	}

	/* normalization - x and y */
	double minX = x[0], maxX = x[num-1];
	for (int i = 0; i < num; i++) {
		x[i] = (x[i] - minX) / (maxX - minX);
	}
	for (int i = 0; i < num; i++) {
		y[i] = y[i] * (maxX - minX);
	}

	/* print to pdf_table.txt */
	gap = x[1] - x[0];
	fprintf(fp_w, "%d %lf\n", num, gap);
	for (int i = 0; i < num; i++) {
		fprintf(fp_w, "%lf %lf\n", x[i], y[i]);
	}

	/* 다시 수치 적분 */
	int a, b, c;
	a = b = c = 0;

	for (int i = 0; i < num; i++) {
		if (x[i] > 0.25) {
			a = i;
			break;
		}
	}
	for (int i = a; i < num; i++) {
		if (x[i] > 0.5) {
			b = i;
			break;
		}
	}
	for (int i = b; i < num; i++) {
		if (x[i] > 0.75) {
			c = i;
			break;
		}
	}

	// 0 ~ 1
	area = 0;
	area += y[0];
	for (int i = 1; i < num - 1; i++) {
		area += 2 * y[i];
	}
	area += y[num - 1];
	area = area / 2 * gap;
	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", area);

	// 0 ~ 0.25
	area = 0;
	area += y[0];
	for (int i = 1; i < a; i++) {
		area += 2 * y[i];
	}
	area += y[a];
	area = area / 2 * gap;
	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", area);

	// 0.25 ~ 0.5
	area = 0;
	area += y[a];
	for (int i = a + 1; i < b; i++) {
		area += 2 * y[i];
	}
	area += y[b];
	area = area / 2 * gap;
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", area);

	// 0.5 ~ 0.75
	area = 0;
	area += y[b];
	for (int i = b + 1; i < c; i++) {
		area += 2 * y[i];
	}
	area += y[c];
	area = area / 2 * gap;
	printf("*** Integrating the pdf from 0.5 to 0.75 = %lf\n", area);

	// 0.75 ~ 1
	area = 0;
	area += y[c];
	for (int i = c + 1; i < num-1; i++) {
		area += 2 * y[i];
	}
	area += y[num-1];
	area = area / 2 * gap;
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", area);

	delete[] x;
	delete[] y;
	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
