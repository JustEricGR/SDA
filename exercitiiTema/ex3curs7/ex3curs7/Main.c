#include<stdio.h>
#include<stdlib.h>

void generare(int* v, int size) {
	
	for (int i = 0; i < size; i++) {
		
		v[i] = size - 1 - i;
	}
	v[3] = v[7];
}

void afisare(int* v, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", v[i]);
	}printf("\n");
}

int cmp(const void* e1, const void* e2) {
	int* v1 = (int*)e1;
	int* v2 = (int*)e2;
	return *v1 - *v2;
}

int verificare(int* v, int size) {
	for (int i = 0; i < size-1; i++) {
		if (v[i] == v[i + 1])return 1;
	}
	return 0;
}

int main(void) {
	int* v = NULL;
	int size = 10;
	v = (int*)malloc(size * sizeof(int));
	

	generare(v, size);
	qsort(v, size, sizeof(int), cmp);
	//ordonam elementele ca sa putem verifica imediat in dreapta fiecarui element daca acesta are vreun duplicat


	afisare(v, size);

	if (verificare(v, size))printf("Sunt duplicate\n");
	else printf("Nu sunt duplicate\n");

	free(v);
}