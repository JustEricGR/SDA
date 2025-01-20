//#include <stdio.h>
//#define N 4
//
//typedef struct coordonate {
//    int linie, coloana;
//} coordonate;
//
//coordonate pos[4]; // Posibilități de deplasare (Nord, Est, Sud, Vest)
//coordonate a[N * N]; // Coordonatele pentru fiecare pas
//int matrice[N][N] = { 0 }; // Matricea
//int culori[4] = { 1, 2, 3, 4 }; // Culorile disponibile
//
//// Inițializează posibilitățile de deplasare (Nord, Est, Sud, Vest)
//void initializare() {
//    pos[0].coloana = 0; pos[0].linie = -1; // Nord
//    pos[1].coloana = 1; pos[1].linie = 0;  // Est
//    pos[2].coloana = 0; pos[2].linie = 1;  // Sud
//    pos[3].coloana = -1; pos[3].linie = 0; // Vest
//}
//
//// Verifică dacă toate celulele din matrice sunt marcate
//int marker() {
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            if (matrice[i][j] == 0) return 0; // Există cel puțin o celulă necompletată
//        }
//    }
//    return 1; // Toate celulele sunt completate
//}
//
//// Determină dacă s-a găsit o soluție completă
//int solutie(int k) {
//    return a[k].linie * a[k].coloana == N * N - 1;
//}
//
//// Verifică dacă o coordonată este validă (în limitele matricei și liberă)
//int acceptabil(coordonate c) {
//    
//    return 1;
//}
//
//// Afișează soluția curentă
//void afiseaza_solutia(int k) {
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            printf("%d ", matrice[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}
//
//// Algoritm de backtracking pentru a umple matricea
//void labirint(int k) {
//    
//
//    for (int j = 0; j < 4; j++) { // Parcurgem fiecare culoare
//        matrice[a[k - 1].linie][a[k - 1].coloana] = culori[j]; // Aplicăm culoarea curentă
//
//        
//        if (acceptabil(a[k])) { // Dacă este validă deplasarea
//            if (solutie(k)) { // Dacă avem o soluție, afișăm matricea
//                afiseaza_solutia(k);
//                
//            }
//            else
//                labirint(k + 1); // Apelăm recursiv pentru pasul următor
//        }
//        
//
//        matrice[a[k - 1].linie][a[k - 1].coloana] = 0; // Restaurăm celula după backtracking
//    }
//}
//
//int main(void) {
//    initializare();
//    a[0].linie = 0;
//    a[0].coloana = 0;
//
//    labirint(1); 
//    return 0;
//}

#include<stdio.h>
#define MAXR 10
#define MAXC 10

int culori[4] = { 1,2,3,4 };


int map[MAXR * MAXC];
int cols = 0;
int rows = 0;

void initMap() {
	for (int i = 0; i < cols * rows; i++) {
		map[i] = 0;
	}
}

void afisare() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", map[i*cols+j]);
		}printf("\n");
	}printf("\n");
}

int nordEst(int k) {
	if (k / rows - 1 < 0 || k % rows - 1 < 0)return 1;
	if (map[k] == map[k - cols - 1])return 0;
	return 1;
}

int nordVest(int k) {
	if (k / rows + 1 < 0 || k % rows + 1 >= MAXC - 1)return 1;
	if (map[k] == map[k - cols + 1])return 0;
	return 1;
}

int sudEst(int k) {
	if (k / rows - 1 >= MAXR - 1 || k % rows + 1 >= MAXC - 1)return 1;
	if (map[k] == map[k + cols - 1])return 0;
	return 1;
}

int sudVest(int k) {
	if (k / rows + 1 >= MAXR - 1 || k % rows - 1 < 0)return 1;
	if (map[k] == map[k + cols + 1])return 0;
	return 1;
}

int valid(int k) {
	if (nordEst(k) && nordEst(k) && sudEst(k) && sudVest(k))return 1;
	return 0;
}

int solutie(int k) {
	return k == rows * cols - 1;
}

void back(int k) {
	for (int i = 0; i < 4; i++) {
		map[k] = culori[i];
		if (valid(k)) {
			if (solutie(k)) {
				afisare();
			}
			else back(k + 1);
		}
		map[k] = 0;
	}
}

int main(void) {
	rows = 4;
	cols = 4;
	back(0);
}

