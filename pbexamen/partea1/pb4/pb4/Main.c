#include<stdio.h>
#include<stdlib.h>

typedef enum {
	NU,
	DA
}Premiu;

typedef struct {
	char nume[35];
	int varsta;
	Premiu premiu;
}Student;

void swap(Student* a, Student* b) {
	Student temp = *a;
	*a = *b;
	*b = temp;
}

Student* citire(Student* v, int size) {
	v = (Student*)malloc(size * sizeof(Student));

	char name[25] = "Student";

	for (int i = 0; i < size; i++) {
		char nume[25] = "";
		sprintf(nume, "%s%d", name, (size-i));
		v[i].varsta = i + (2*(i+1));
		strcpy(v[i].nume, nume);
		v[i].premiu = i % 2;
	}

	return v;
}

void afisare(Student* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("Nume: %s; varsta:%d; premiu:%u\n", v[i].nume, v[i].varsta, v[i].premiu);
	}
}

void modif1(Student* v, int size, int *poz) {
	int start = 0;
	for (int i = 0; i < size; i++) {
		if (start >= size - start)break;
		if (v[i].premiu) {
			swap(&v[i], &v[start++]);
		}
	}
	*poz = start;
}

void quicksort(Student a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	Student pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && strcmp(a[stanga].nume, pivot.nume)<0)
			stanga++;
		while (dreapta >= prim && strcmp(pivot.nume, a[dreapta].nume)<0)
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

int main(void) {
	Student* v = NULL;
	int size = 7;
	int pozitie = 0;
	v = citire(v, size);
	afisare(v, size);

	printf("Dupa modificarea1:\n");
	modif1(v, size, &pozitie);
	afisare(v, size);

	printf("Dupa modificarea2:\n");
	quicksort(v, 0, pozitie-1);
	afisare(v, size);


	free(v);
}
