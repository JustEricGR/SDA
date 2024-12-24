#include<stdio.h>
#include<stdlib.h>

void generare(int* v, int size) {
	for (int i = 0; i < size; i++) {
		v[i] = size - 1 - i;
	}
}

int find(int* v, int stanga, int dreapta) {
	if (stanga > dreapta)return -1;
	int mid = (stanga + dreapta) / 2;
	if (v[mid] == mid) {
		return mid;
	}
	else if (v[mid] < mid) {
		return find(v, mid + 1, dreapta);
	}
	else {
		return find(v, stanga, mid-1);
	}
}

int main(void) {
	int* v = NULL;
	int size = 9;
	v = (int*)malloc(size * sizeof(int));
	generare(v, size);

	printf("Gasit:%d\n", find(v, 0, size - 1));

	free(v);
}