#include <stdio.h>
#define N 4

typedef struct coordonate
{
	int linie, coloana;
}coordonate;
coordonate pos[4];
coordonate a[N * N];
int matrice[N][N] = { 4,5,2,1,
				   1,3,4,1,
				   5,2,3,2,
				   1,2,2,5 };

void initializare() //int pos[] variabila globala
{	//initializarea posibilitatilor de deplasare Posibilitățile de deplasare sunt Nord, Est, Sud, Vest
	pos[0].coloana = 0; // Nord
	pos[0].linie = -1;// y scade spre Nord
	pos[1].coloana = 1; // Est – x creste spre Est
	pos[1].linie = 0;
	pos[2].coloana = 0; // Sud
	pos[2].linie = 1; // y creste spre Sud
	pos[3].coloana = -1;// Vest – x scade spre Vest
	pos[3].linie = 0;
}
int solutie(int k, coordonate c)
{
	if (c.coloana == 0 || c.linie == 0 || c.coloana == N - 1 || c.linie == N - 1) //daca am ajuns la margine
		return 1;
	else
		return 0;
}

int acceptabil(coordonate c, int k) {
	if (c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N &&
		matrice[c.linie][c.coloana] != -1 && // Verifică dacă nu e vizitat
		matrice[c.linie][c.coloana] <= k) {
		return 1;
	}
	return 0;
}


void afiseaza_solutia(int k)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			printf("%d\t", matrice[i][j]);
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < k; i++)
		printf("pas %d = %d-%d\n", i, a[i].linie, a[i].coloana);
	printf("\n");
}

void labirint(int k, int precedent) {
	if (solutie(k, a[k - 1])) {
		int n = matrice[a[0].linie][a[0].coloana];
		matrice[a[0].linie][a[0].coloana] = -1;
		afiseaza_solutia(k);
		matrice[a[0].linie][a[0].coloana] = n;
	}
	else {
		for (int i = 0; i < 4; i++) {
			coordonate aux;
			aux.linie = a[k - 1].linie + pos[i].linie;
			aux.coloana = a[k - 1].coloana + pos[i].coloana;

			if (acceptabil(aux, precedent)) {
				a[k] = aux;
				int n = matrice[aux.linie][aux.coloana];
				matrice[aux.linie][aux.coloana] = -1; // Marchează ca vizitat
				labirint(k + 1,n);
				matrice[aux.linie][aux.coloana] = n; // Restaurează valoarea
			}
		}
	}
}

int main(void)
{
	initializare();
	printf("dati linia initiala ");
	scanf("%d", &a[0].linie);
	printf("dati coloana initiala ");
	scanf("%d", &a[0].coloana);
	
	labirint(1,matrice[a[0].linie][a[0].coloana]);
	matrice[a[0].linie][a[0].coloana] = -1; //marchez ca vizitat
	return 0;
}