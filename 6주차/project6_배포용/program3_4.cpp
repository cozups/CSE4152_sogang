#include "my_solver.h"


void program3_4() {
    int i, ia, j, n;

    FILE* fp_r = fopen("linear_system_3-4.txt", "r");
    if (fp_r == NULL) {
        printf("file open error...\n");
        return;
    }
    FILE* fp_w = fopen("solution_3-4.txt", "w");
    if (fp_w == NULL) {
        printf("%s file open error...\n", "solution_3-4.txt");
        return;
    }

    fscanf(fp_r, "%d", &n);
    fprintf(fp_w, "%d\n", n);
    ia = n;
    float* a = new float[n * n];
    float* b = new float[n];
    float* x = new float[n];
    float* s = new float[n];
    int* l = new int[n];

    float** mat;
    mat = new float* [n];
    for (i = 0; i < n; i++)
        mat[i] = new float[n];

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            float tmp;
            fscanf(fp_r, "%f", &tmp);
            a[j * n + i] = tmp;
            mat[i][j] = tmp;
        }
    }
    for (i = 0; i < n; i++) {
        fscanf(fp_r, "%f", &b[i]);
    }

    /********************************/
    printf("--------------------------program3_4--------------------------\n");
    
    gespp_(&n, a, &ia, l, s);
    solve_(&n, a, &ia, l, b, x);
    printf("---------solved---------\n");
    printf("%d\n", n);
    for (i = 0; i < n; i++) {
        printf("%.6f\n", x[i]);
        fprintf(fp_w, "%.6f\n", x[i]);
    }
    printf("\n");

    float sum = 0, sqsum = 0, bsqsum = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            sum += mat[i][j] * x[j];
        }
        sum -= b[i];
        sqsum += sum * sum;
        sum = 0;
        bsqsum += b[i] * b[i];
    }

    printf("%.6f\n", sqrt(sqsum) / sqrt(bsqsum));
    fprintf(fp_w, "%.6f\n", sqrt(sqsum) / sqrt(bsqsum));


    delete[] a;
    delete[] b;
    delete[] x;
    delete[] s;
    delete[] l;


    if (fp_r != NULL) fclose(fp_r);
    if (fp_w != NULL) fclose(fp_w);
    /********************************/

}
