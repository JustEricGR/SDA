#include<stdio.h>
#include<stdlib.h>
#include "timer.h"

void generare(int* v, int size) {
	for (int i = 0; i < size; i++) {
		v[i] = size - i - 1;
	}
	
}

void afisare(int* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", v[i]);
	}printf("\n");
}


#define T 3
int h[T];
void genereare_incrementi_fib(int h[], int t)
{
	int i;
	//generare tablou de incrementi
	/*h[T - 1] = 1;
	for (i = T - 2; i >=0; i--)
	{
		h[i] = 3 * h[i + 1] + 1;
	}*/
	int fib[T + 2];
	fib[0] = 0;
	fib[1] = 1;
	for (i = 2; i < T+2; i++) {
		fib[i] = fib[i - 1] + fib[i-2];
		//h[i] = fib[i + 2];
	}

	for (int i = 0; i < T; i++) {
		h[i] = fib[T + 1 - i];
	}
}



#define T1 3
int h[T1];
void generare_incrementi_speciali(int h[], int t)
{
	int i;
	//generare tablou de incrementi
	/*h[T - 1] = 1;
	for (i = T - 2; i >=0; i--)
	{
		h[i] = 3 * h[i + 1] + 1;
	}*/
	//int [T1 + 2];
	//fib[0] = 0;
	//fib[1] = 1;
	//for (i = 2; i < T1 + 2; i++) {
	//	fib[i] = fib[i - 1] + fib[i - 2];
	//	//h[i] = fib[i + 2];
	//}
	h[T1 - 1] = 1;

	for (int i = T1-2; i >= 0; i--) {
		h[i] = h[i + 1] * 3 + 1;
	}
}
void shell_sort(int* a, int n)
{

	int i, j, k, hCnt, H;
	int tmp;
	generare_incrementi_speciali(h, T1);
	//pentru fiecare increment
	for (i = 0; i < T; i++)
	{
		H = h[i]; //incrementul curent
		//pentru fiecare subtablou
		for (hCnt = 0; hCnt < H; hCnt++)
		{ //insetion_sort pentru subtablou
			for (j = H + hCnt; j < n; j += H)
			{
				tmp = a[j];
				for (k = j; (k - H >= 0) && tmp < a[k - H]; k -= H)
					a[k] = a[k - H];
				a[k] = tmp;
			}
		}
	}
}

int main(void) {
	int size = 50000;
	int* v = (int*)malloc(size * sizeof(int));
	generare(v, size);
	//afisare(v, size);
	starton();
	shell_sort(v, size);
	printf("Total time: %.7g", startoff());
	//startoff();
	
	//afisare(v, size);
	//printf("Timp pt shellsort cu incrementi fibonacci: %.6g\n", time1);


	/*starton();
	for(int i=0;i<1000000000;i++){}
	startoff();*/
	free(v);
}