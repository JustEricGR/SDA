#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char nume[25];
	int puncte;
	int buget;
	char oras[25];
}Echipa;

void swap(Echipa* a, Echipa* b) {
	Echipa tmp = *a;
	*a = *b;
	*b = tmp;
}

Echipa* citire(Echipa* v, int size) {
	v = (Echipa*)calloc(size, sizeof(Echipa));

	char name[25] = "Nume";
	char city[25] = "Oras";

	for (int i = 0; i < size; i++) {
		char nume[25] = "";
		char oras[25] = "";
		sprintf(nume, "%s%d", name, i + 1);
		sprintf(oras, "%s%d", city, i + 1);
		v[i].buget = 200000 - 20000 * i;
		v[i].puncte = (i + 1) * 10;

		strcpy(v[i].nume, nume);
		strcpy(v[i].oras, oras);
	}

	return v;
}

void afisare(Echipa* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("Nume: %s; oras: %s; buget:%d; puncte:%d\n", v[i].nume, v[i].oras, v[i].buget, v[i].puncte);
	}
}

void modif1(Echipa* v, int size) {
	int marker1 = 0;
	for (int i = 0; i < size; i++) {
		if (size - marker1 <= marker1)break;
		if (v[i].puncte > 45) {
			swap(&v[i], &v[marker1++]);
		}
	}

	int marker2 = size - 1;
	for (int i = marker1; i < size; i++) {
		if (marker2-i<=0)break;
		if (v[i].puncte <= 20) {
			swap(&v[i], &v[marker2--]);
			
		}
	}
}

void selection_sort(Echipa a[], int n)
{
	int i, j, min; // min retine INDEXUL elementului cu valoare minima
	for (i = 0; i < n - 1; i++)
	{
		if (a[i].buget > 100000)
			min = i;
		else continue;
		for (j = i + 1; j < n; j++)
		{
			if (a[j].buget > a[min].buget)
				min = j;
		}
		swap(&a[min], &a[i]);
	}
}

int main(void) {
	Echipa* v = NULL;
	int size = 7;
	v = citire(v, size);

	afisare(v, size);

	modif1(v, size);
	printf("Dupa prima modificare:\n");
	afisare(v, size);

	selection_sort(v, size);
	printf("Dupa a doua modificare:\n");
	afisare(v, size);

	free(v);
}