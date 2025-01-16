#include<stdio.h>

typedef enum {
	ALB,
	GALBEN,
	ROSU,
	VERDE,
	ALBASTRU,
	NEGRU
}Culori;

Culori v[3];
int n = 3;

void afisare() {
	for (int i = 0; i < n; i++) {
		switch (v[i]) {
			case ALB :
				printf("alb ");
				break;
			case GALBEN :
				printf("galben ");
				break;
			case ROSU :
				printf("rosu ");
				break;
			case VERDE :
				printf("verde ");
				break;
			case ALBASTRU :
				printf("albastru ");
				break;
			case NEGRU :
				printf("negru ");
				break;

		}
	}printf("\n");
}

int valid(int k) {
	for (int i = 0; i < k; i++) {
		if (v[i] == v[k])return 0;
	}
	return 1;
}

int solutie(int k) {
	return k == n - 1 && (v[n / 2] == VERDE || v[n / 2] == GALBEN);
}

void back(int k) {
	for (unsigned int i = 0; i < 6; i++) {
		v[k] = i;
		if (valid(k)) {
			if (solutie(k)) {
				afisare();
			}
			else {
				back(k + 1);
			}
		}
	}
}

int main(void) {
	back(0);
}