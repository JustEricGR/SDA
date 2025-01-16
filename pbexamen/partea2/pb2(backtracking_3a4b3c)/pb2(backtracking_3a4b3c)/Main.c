#include<stdio.h>
#include<string.h>

char m[3] = { 'a','b','c' };
char v[10] = "";
int n = 10;

void afisare() {
	for (int i = 0; i < n; i++) {
		printf("%c ", v[i]);
	}printf("\n");
}

int valid(int k) {
	int frecventa[3] = { 0,0,0 };
	//memset(frecventa, 0, 3);
	for (int i = 0; i <= k; i++) {
		//printf("%c ", v[i]);
		frecventa[v[i] - 'a']++;
	}
	return frecventa[0] <= 3 && frecventa[1] <= 4 && frecventa[2] <= 3;
}

int solutie(int k) {
	int frecventa[3] = { 0,0,0 };

	for (int i = 0; i <= k; i++) {
		//printf("%c ", v[i]);
		frecventa[v[i] - 'a']++;
	}
	return frecventa[0] == 3 && frecventa[1] == 4 && frecventa[2] == 3 && k == n - 1;
}

void back(int k, int *nrsol) {
	for (int i = 0; i < 3; i++) {
		v[k] = m[i];
		if (valid(k)) {
			if (solutie(k)) {
				if (*nrsol>=0) {
					afisare();
					*nrsol-=1;
					//printf("Nrsol:%d\n", *nrsol);
				}
				
			}
			else {
				back(k + 1, nrsol);
			}
		}
	}
}

int main(void) {
	int nrsol = 5;
	back(0,&nrsol);
}