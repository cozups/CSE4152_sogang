#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>

#include <math.h>
#include <time.h>
#include <Windows.h>

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;
float compute_time1, compute_time2;

#define MATDIM 1024
#define HW1_N 100000
float *hw1_x, hw1_E, hw1_var1, hw1_var2;
float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];

/* hw1 */
void init_hw1(int fixed);
void hw1_calc_e();
void hw1_calc_var1();
void hw1_calc_var2();
/* hw2 */
void hw2_naive();
void hw2_safe();
float hw2_verify(float x);
/* hw3 */
void hw3_1();
void hw3_2();
void hw3_3();
void hw3_4();
void hw3_5();


void main(void)
{
	srand((unsigned)time(NULL));

	/* hw1 */
	puts("====== hw1 ======");
	init_hw1(1);
	CHECK_TIME_START;
	hw1_calc_var1();
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw1_calc_var1 = %f ms\n", compute_time);
	printf("hw1_calc_var1 value = %.15f\n", hw1_var1);


	CHECK_TIME_START;
	hw1_calc_e();
	hw1_calc_var2();
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw1_calc_var2 = %f ms\n", compute_time);
	printf("hw1_calc_var2 value = %.15f\n", hw1_var2);
	puts("");
	
	/* hw2 */
	puts("====== hw2 ======");
	printf("a, b, c : ");
	scanf("%f %f %f", &hw2_a, &hw2_b, &hw2_c);
	hw2_naive();
	printf("naive result    : %.15f, %.15f\n", hw2_naive_ans[0], hw2_naive_ans[1]);
	hw2_safe();
	printf("advanced result : %.15f, %.15f\n", hw2_pre_ans[0], hw2_pre_ans[1]);
	puts("");
	printf("Verifying naive ans    : %.15f, %.15f\n", hw2_verify(hw2_naive_ans[0]), hw2_verify(hw2_naive_ans[1]));
	printf("Verifying advanced ans : %.15f, %.15f\n", hw2_verify(hw2_pre_ans[0]), hw2_verify(hw2_pre_ans[1]));
	puts("");

	/* hw3 */
	puts("====== hw3 ======");
	printf("1. Loop collapsing\n");
	hw3_1();
	printf("\n2. Code motion\n");
	hw3_2();
	printf("\n3. Dead code elimination\n");
	hw3_3();
	printf("\n4. Induction variable & Strength reduction\n");
	hw3_4();
	printf("\n5. Integer divide optimization\n");
	hw3_5();
}

void init_hw1(int fixed)
{
	float *ptr;
	hw1_x = (float *)malloc(sizeof(float)*HW1_N);

	if (fixed)
	{
		float tmp = HW1_N;
		for (int i = 0; i < HW1_N; i++)
		{
			if( i & 1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		srand((unsigned)time(NULL));
		ptr = hw1_x;
		for (int i = 0; i < HW1_N; i++)
			*ptr++ = ((float)rand() / (float)RAND_MAX) * 2;
	}
}
void hw1_calc_e()
{
	hw1_E = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_E += hw1_x[i];
	}
	hw1_E /= (float)HW1_N;
}
void hw1_calc_var1()
{
	hw1_var1 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_var1 += (hw1_x[i]* hw1_x[i]);
	}
	hw1_var1 *= HW1_N;

	float tmp = 0;
	for (int i = 0; i < HW1_N; i++) {
		tmp += hw1_x[i];
	}
	hw1_var1 -= tmp * tmp;
	hw1_var1 /= (HW1_N * (HW1_N - 1));
}
void hw1_calc_var2()
{
	hw1_var2 = 0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_var2 += ((hw1_x[i] - hw1_E) * (hw1_x[i] - hw1_E));
	}
	hw1_var2 /= (HW1_N - 1);
}


/* hw2 */
void hw2_naive()
{
	hw2_naive_ans[0] = -hw2_b + sqrt((hw2_b * hw2_b) - (4.0 * hw2_a * hw2_c));
	hw2_naive_ans[0] /= 2.0 * hw2_a;

	hw2_naive_ans[1] = -hw2_b - sqrt((hw2_b * hw2_b) - (4.0 * hw2_a * hw2_c));
	hw2_naive_ans[1] /= 2.0 * hw2_a;
}
void hw2_safe()
{
	double temp;
	if (hw2_b >= 0) {
		temp = ((-4) * hw2_a * hw2_c) / (hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
		hw2_pre_ans[0] = temp / (2 * hw2_a);

		temp = (-hw2_b) - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c);
		hw2_pre_ans[1] = temp / (2 * hw2_a);
	}
	else {
		temp = (-hw2_b) + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c);
		hw2_pre_ans[0] = temp / (2 * hw2_a);

		temp = ((-4) * hw2_a * hw2_c) / (hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
		hw2_pre_ans[1] = temp / (2 * hw2_a);
	}
}
float hw2_verify(float x)
{
	return hw2_a * x * x + hw2_b*x + hw2_c;
}
void hw3_1() {
	srand((unsigned)time(NULL));
	float a[10000][1000];

	CHECK_TIME_START;
	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < 10000; j++)
			a[j][i] = 0;
	CHECK_TIME_END(compute_time);
	printf("hw3_1_original = %.15f ms\n", compute_time);
	
	float* p = &a[0][0];
	CHECK_TIME_START;
	for (int i = 0; i < 90000; i++)
		*p++ = 0;
	CHECK_TIME_END(compute_time);
	printf("hw3_1_optimized = %.15f ms\n", compute_time);

}
void hw3_2() {
	srand((unsigned)time(NULL));
	int n = 10000000;
	int i = 0;
	float x, y = 10.5, z = 11.27;
	float a;
	CHECK_TIME_START;
	while (i < n) {
		x = y + z;
		a = 6 * i + x * x;
		++i;
	}
	CHECK_TIME_END(compute_time);
	printf("a: %.15f\n", a);
	printf("hw3_2_original = %.15f ms\n", compute_time);
	
	i = 0;
	CHECK_TIME_START;
	if (i < n) {
		x = y + z;
		float const t1 = x * x;
		do {
			a = 6 * i + t1;
			++i;
		} while (i < n);
	}
	CHECK_TIME_END(compute_time);
	printf("a: %.15f\n", a);
	printf("hw3_2_optimized = %.15f ms\n", compute_time);
}
void hw3_3() {
	srand((unsigned)time(NULL));
	CHECK_TIME_START;
	for (int i = 0; i < 10000000; i++) {
		float hw3_a = 11.27, hw3_b = 12.34;
		float c = hw3_a * hw3_b;
		float x = hw3_a;
		float y = x;
		float z = y;
		float d = hw3_a * hw3_b + 4;
		if (0) {
			printf("hello world!\n");
		}
		if (0) {
			printf("hi!\n");
		}
		if (0) {
			printf("bye!\n");
		}
	}
	CHECK_TIME_END(compute_time);
	printf("hw3_3_original = %.15f ms\n", compute_time);
	
	CHECK_TIME_START;
	for (int i = 0; i < 10000000; i++) {
		float hw3_a = 11.27, hw3_b = 12.34;
		float d = hw3_a * hw3_b + 4;
	}
	CHECK_TIME_END(compute_time);
	printf("hw3_3_optimized = %.15f ms\n", compute_time);
}
void hw3_4() {
	srand((unsigned)time(NULL));
	int i;
	float j, k;
	CHECK_TIME_START;
	for (i = 0; i < 10000000; ++i) {
		j = 17.0 * i;
		k = 23.5 * i;
	}
	CHECK_TIME_END(compute_time);
	printf("j: %.15f k: %.15f\n", j, k);
	printf("hw3_4_original = %.15f ms\n", compute_time);

	CHECK_TIME_START;
	j = -17;
	k = -23.5;
	for (i = 0; i < 10000000; ++i) {
		j = j + 17;
		k = k + 23.5;
	}
	CHECK_TIME_END(compute_time);
	printf("j: %.15f k: %.15f\n", j, k);
	printf("hw3_4_optimized = %.15f ms\n", compute_time);
}
void hw3_5() {
	srand((unsigned)time(NULL));
	float a, b, c;
	CHECK_TIME_START;
	for (int i = 0; i < 10000000; i++) {
		a = i / 2;
		b = i / 4;
		c = i / 8;
	}
	CHECK_TIME_END(compute_time);
	printf("a: %.15f b: %.15f c: %.15f\n", a, b, c);
	printf("hw3_5_original = %.15f ms\n", compute_time);

	CHECK_TIME_START;
	for (int i = 0; i < 10000000; i++) {
		a = i >> 1;
		b = i >> 2;
		c = i >> 3;
	}
	CHECK_TIME_END(compute_time);
	printf("a: %.15f b: %.15f c: %.15f\n", a, b, c);
	printf("hw3_5_optimized = %.15f ms\n", compute_time);
}