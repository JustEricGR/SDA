#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char nume[25];
	char oras[25];
	int puncte;
	int buget;
}Echipa;

typedef struct {
	int indix;
	Echipa element;
}Indici;

void swap(Echipa* a, Echipa* b) {
	Echipa aux;
	aux = *a;
	*a = *b;
	*b = aux;
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
		v[i].buget = 200000 - 20000*i;
		v[i].puncte = (i+1)*10;
		
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
		if (marker1 >= size - marker1)break;
		if (v[i].puncte > 45) {
			swap(&v[i], &v[marker1++]);
		}
	}

	int marker2 = size - 1;
	for (int i = marker1; i < size; i++) {
		if (marker2 - marker1 <= 0)break;
		if (v[i].puncte <= 20) {
			swap(&v[i], &v[marker2--]);
			marker1++;
		}
	}
}

void quicksort(Indici a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&(a[prim].element), &(a[(prim + ultim) / 2].element));
	//mutare pivot pe prima pozitie
	Indici pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga <= ultim && a[stanga].element.buget > pivot.element.buget)
			stanga++;
		while (dreapta >= prim && pivot.element.buget > a[dreapta].element.buget)
			dreapta--;
		if (stanga < dreapta)
			swap(&(a[stanga++].element), &(a[dreapta--].element));
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&(a[dreapta].element), &(a[prim].element));
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}

void modif2(Echipa* v, int size) {
	int nrElem = 0;
	Indici* indici = (Indici*)malloc(size * sizeof(Indici));
	for (int i = 0; i < size; i++) {
		if (v[i].buget > 100000) {
			indici[nrElem].element = v[i];
			indici[nrElem].indix = i;
			nrElem++;
		}
	}

	quicksort(indici, 0, nrElem - 1);
	

	for (int i = 0; i < nrElem; i++) {
		v[indici[i].indix] = indici[i].element;
	}

	free(indici);
}


int main(void) {
	Echipa* v = NULL;
	int size = 7;
	v = citire(v, size);

	afisare(v, size);

	printf("Dupa prima modificare:\n");
	modif1(v, size);
	afisare(v, size);

	
	modif2(v, size);
	printf("Dupa a doua modificare:\n");
	afisare(v, size);

	free(v);
}