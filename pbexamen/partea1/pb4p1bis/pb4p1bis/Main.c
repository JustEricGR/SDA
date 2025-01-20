#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char nume[25];
	char telefon[11];
	int an;
	int venit;
	int varsta;
}Agenda;

typedef struct {
	Agenda element;
	int pozitie;
}Indici;

void swap(Agenda* a, Agenda* b) {
	Agenda aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

Agenda* citire(Agenda* v, int size) {
	v = (Agenda*)calloc(size, sizeof(Agenda));

	char name[25] = "Nume";
	char telefon[11] = "0256167772";

	for (int i = 0; i < size; i++) {
		char nume[25] = "";
		sprintf(nume, "%s%d", name, i + 1);
		v[i].an = 2010 - (i + 2) * 4;
		v[i].varsta = 2025 - v[i].an;
		v[i].venit = 985 + 5 * i;
		strcpy(v[i].nume, nume);
		strcpy(v[i].telefon, telefon);
	}

	return v;
}

void afisare(Agenda* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("Nume: %s; telefon: %s; an:%d; venit:%d, varsta:%d\n", v[i].nume, v[i].telefon, v[i].an, v[i].venit, v[i].varsta);
	}
}

void modificare1(Agenda* v, int size) {
	int flag = 0;
	for (int i = 0; i < size; i++) {
		if (flag == 2)break;
		if (v[i].venit < 1000) {
			swap(&v[i], &v[size - 1 - flag]);
			flag++;
		}
	}
}

void selection_sort(Agenda* a, int n)
{
	int i, j, min; // min retine INDEXUL elementului cu valoare minima
	for (i = 0; i < n - 1; i++)
	{
		if (a[i].varsta > 30 && a[i].varsta < 40)
			min = i;
		else
			continue;
		for (j = i + 1; j < n; j++)
		{
			if (a[j].varsta > 30 && a[j].varsta < 40) {
				if (strcmp(a[j].nume, a[min].nume) < 0)
					min = j;
			}
			
		}
		swap(&a[min], &a[i]);
	}
}

//void quicksort(Agenda a[], int prim, int ultim)
//{
//	while (prim <= ultim && (a[prim].varsta <= 30 || a[prim].varsta >= 40)) {
//		prim++;
//	}
//	int stanga = prim + 1;
//	int dreapta = ultim;
//	//alegere pivot
//	swap(&a[prim], &a[(prim + ultim) / 2]);
//	//mutare pivot pe prima pozitie
//	Agenda pivot = a[prim];
//	while (stanga <= dreapta) //partitionare
//	{
//		while (stanga <= ultim && strcmp(a[stanga].nume, pivot.nume)<0)
//			stanga++;
//		while (dreapta >= prim && strcmp(pivot.nume, a[dreapta].nume)<0)
//			dreapta--;
//		if (stanga < dreapta)
//			swap(&a[stanga++], &a[dreapta--]);
//		else
//			stanga++;
//	}
//	//mutare pivot la locul sau final
//	swap(&a[dreapta], &a[prim]);
//	//apelurile recursive
//	if (prim < dreapta - 1)
//		quicksort(a, prim, dreapta - 1);
//	if (dreapta + 1 < ultim)
//		quicksort(a, dreapta + 1, ultim);
//}

void modificare2(Agenda* v, int size) {
	int sizeVect = 0;
	/*Agenda* elemente = (Agenda*)malloc(size * sizeof(Agenda));
	int* pozitii = (int*)malloc(size * sizeof(int));*/
	Indici* indici = (Indici*)malloc(size * sizeof(Indici));
	for (int i = 0; i < size; i++) {
		if (v[i].varsta >= 30 && v[i].varsta <= 40) {
			indici[sizeVect].element = v[i];
			indici[sizeVect].pozitie = i;
			sizeVect++;
		}
	}
	/*printf("Afisare inainte de sortare:\n");
	for (int i = 0; i < sizeVect; i++) {
		printf("Indice:%d\n", indici[i].pozitie);
		printf("Nume: %s; telefon: %s; an:%d; venit:%d, varsta:%d\n", indici[i].element.nume, indici[i].element.telefon, indici[i].element.an, indici[i].element.venit, indici[i].element.varsta);
	}*/
	selection_sort(indici, sizeVect);
	/*printf("Dupa sortare:\n");
	for (int i = 0; i < sizeVect; i++) {
		printf("Indice:%d\n", indici[i].pozitie);
		printf("Nume: %s; telefon: %s; an:%d; venit:%d, varsta:%d\n", indici[i].element.nume, indici[i].element.telefon, indici[i].element.an, indici[i].element.venit, indici[i].element.varsta);
	}*/

	for (int i = 0; i < sizeVect; i++) {
		strcpy(v[indici[i].pozitie].nume, indici[i].element.nume);
		strcpy(v[indici[i].pozitie].telefon, indici[i].element.telefon);
		v[indici[i].pozitie].an = indici[i].element.an;
		v[indici[i].pozitie].venit = indici[i].element.venit;
		v[indici[i].pozitie].varsta = indici[i].element.varsta;
	}

	free(indici);
}

int cmp(const void* e1, const void* e2) {
	Agenda* v1 = (Agenda*)e1;
	Agenda* v2 = (Agenda*)e2;
	return v1->an - v2->an;
}

int main(void) {
	Agenda* v = NULL;
	int size = 9;
	v = citire(v, size);
	afisare(v, size);
	qsort(v, size, sizeof(Agenda), cmp);
	printf("Dupa rearanjare:\n");
	afisare(v, size);

	//modificare1(v, size);
	//quicksort(v, 0, size-1);
	selection_sort(v, size);
	printf("Dupa modificare:\n");
	afisare(v, size);

	free(v);
}