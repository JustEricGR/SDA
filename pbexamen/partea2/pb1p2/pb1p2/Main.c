#include<stdio.h>

int v[10] = { 0,7,9,9 };
int n = 10;

void afisare() {
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}printf("\n");
}

int valid(int k) {
	for (int i = 4; i < k; i++) {
		if ((v[i] % 2 == 0) && (v[i + 1] % 2 == 0))return 0;
	}
	return 1;
	
}

int solutie(int k) {
	
	return v[n-1] == 0 ;
}

//int valid(int k) {
//	for (int i = 0; i < k; i++) {
//		if (v[i] == v[k])return 0;
//	}
//	return 1;
//}
//
//int solutie(int k) {
//	return k == n - 1;
//}

void back(int k) {
	if (k == n) {
		if (solutie(k)) {
			afisare();
		}
		return;
	}
	for (int i = 0; i < n; i++) {
		v[k] = i;
		//afisare();
		if (valid(k)) {
			//printf("valid\n");
			//afisare();
			
			back(k + 1);
			
		}
	}
}

int main(void) {
	back(4);
}