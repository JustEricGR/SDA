#include<stdio.h>
#include<stdlib.h>

typedef enum {
	NU,
	DA
}Bonus;

typedef struct {
	char nume[35];
	int salar;
	Bonus bonus;
}Angajat;

void swap(Angajat* a, Angajat* b) {
	Angajat temp = *a;
	*a = *b;
	*b = temp;
}

Angajat* citire(Angajat* v, int size) {
	v = (Angajat*)malloc(size*sizeof(Angajat));

	char name[25] = "Nume";
	char telefon[11] = "0256167772";

	for (int i = 0; i < size; i++) {
		char nume[25] = "";
		sprintf(nume, "%s%d", name, i + 1);
		v[i].salar = (i + 3) * 700;
		v[i].bonus = i % 2;
		strcpy(v[i].nume, nume);
		
	}

	return v;
}

void afisare(Angajat* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("Nume: %s; salariu:%d; bonus:%u\n", v[i].nume, v[i].salar, v[i].bonus);
	}
}

void modif1(Angajat* v, int size, int *poz) {
	int pozitie = 0;
	for (int i = 0; i < size; i++) {
		if (size - pozitie < pozitie)break;
		if (v[i].bonus) {
			swap(&v[i], &v[pozitie++]);
		}
	}
	*poz = pozitie;
}


void quicksort(Angajat a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	//swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	Angajat pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && a[stanga].salar > pivot.salar)
			stanga++;
		while (dreapta >= prim && pivot.salar > a[dreapta].salar)
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
	Angajat* v = NULL;
	int pozitie = 0;
	int size = 7;
	v = citire(v, size);
	afisare(v, size);

	printf("Dupa modificarea1:\n");
	modif1(v, size, &pozitie);
	afisare(v, size);

	printf("Dupa modificarea2:\n");
	quicksort(v, pozitie, size - 1);
	afisare(v, size);
	free(v);
}