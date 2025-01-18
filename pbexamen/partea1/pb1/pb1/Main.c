#include <stdio.h>
#include<stdlib.h>

int *generare(int n)
{
	int* a = (int*)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++) {
		a[i] = n - i - 5;
	}
	return a;
}



void swap(int* el1, int* el2)
{
	int tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}


void quicksort(int* a, int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	int pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && a[stanga] < pivot)
			stanga++;
		while (dreapta >= prim && pivot < a[dreapta])
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}


void afisare(int* a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int* schimbare(int* a, int n) {
	int inceput = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] < 0) {
			swap(&a[i], &a[inceput++]);
		}
	}
	afisare(a, n);
	quicksort(a, inceput, n - 1);
	return a;
}

int main(void)
{
	int* a=NULL;
	
	int n = 10;
	a=generare(n);
	afisare(a, n);

	//quicksort(a, 0, n - 1);
	a=schimbare(a, n);
	afisare(a, n);
	free(a);
	return 0;
}