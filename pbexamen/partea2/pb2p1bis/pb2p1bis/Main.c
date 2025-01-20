#include<stdio.h>

char v[10] = "";
int n = 10;

void afisare() {
	for (int i = 0; i < n; i++) {
		printf("%c ", v[i]);
	}printf("\n");
}

int valid(int k) {
	int frecvente[3] = { 0,0,0 };
	for (int i = 0; i <= k; i++) {
		frecvente[v[i] - 'a']++;
	}
	return frecvente[0] <= 3 && frecvente[1] <= 4 && frecvente[2] <= 3;
}

int solutie(int k) {
	int frecvente[3] = { 0,0,0 };
	for (int i = 0; i <= k; i++) {
		frecvente[v[i] - 'a']++;
	}
	return k == n - 1 && frecvente[0] == 3 && frecvente[1] == 4 && frecvente[2] == 3;;
}

void back(int k) {
	for (char i = 'a'; i <= 'c'; i++) {
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
