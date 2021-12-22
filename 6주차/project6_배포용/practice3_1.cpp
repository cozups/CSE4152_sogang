#include "my_solver.h"

void practice3_1() {
    int i, ia, j, n, l[4];
    // f1: 2x^4 + x = 3
    // f2: 4x^4 + 2x^3 + 3x^2 + x = 10
    // f3: 4x^3 + 5x^2 + 2x = 11
    // f4: x^4 + 2x^3 + 2x^2 + 3x = 8
    float a[16] = {
        2, 4, 0, 1,
        0, 2, 4, 2,
        0, 3, 5, 2,
        1, 1, 2, 3 },
        b[4] = { 3, 10, 11, 8 },
        x[4] = { 0, 0, 0, 0 },
        s[4] = { 0, 0, 0, 0 };

    /********************************/
    printf("--------------------------practice3_1--------------------------\n");
    n = ia = 4;
    printf("---------coefficient---------\n");
    for (i = 0; i < 16; i++) {
        if (i % 4 == 0) printf("\n");
        printf("%.2f ", a[i]);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf("%.2f ", b[i]);
    }
    printf("\n");

    gespp_(&n, a, &ia, l, s);
    solve_(&n, a, &ia, l, b, x);
    printf("---------solved---------\n");
    for (i = 0; i < 4; i++) {
        printf("%f ", x[i]);
    }
    printf("\n");


    /********************************/

}
