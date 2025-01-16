#include <stdio.h>
#include <string.h>
#define N 4

typedef struct coordonate
{
	int linie, coloana;
}coordonate;
coordonate pos[4];
coordonate a[N * N];
int matrice[N][N] = { 1,0,0,1,
				   0,1,0,0,
				   0,1,1,1,
				   0,1,0,1 };

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

void clear(int k) {
	memset(a, 0, k);
}

void afiseaza_solutia(int k)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			printf("%d ", matrice[i][j]);
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < k; i++)
		printf("pas %d = %d-%d\n", i, a[i].linie, a[i].coloana);
	printf("\n");
}

int solutie(int k, coordonate c)
{
	
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrice[a[i].linie + pos[j].linie][a[i].coloana + pos[j].coloana] == 1) {
				//printf("pas %d = %d-%d\n", i, a[i].linie, a[i].coloana);
				return 0;
			}
		}
	}
	//afiseaza_solutia(k);
	return 1;
}
int acceptabil(coordonate c)
{
	if (matrice[c.linie][c.coloana] == 1 && c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N) //daca este liber si coordonata se afla in dimensiunile matricei
		return 1;
	else return 0;
}


void labirint(int k)  
{
	int i; coordonate aux;
	if (solutie(k, a[k - 1]))        
		afiseaza_solutia(k);
	else
	{
		for (i = 0; i < 4; i++)  
		{
			aux.coloana = a[k - 1].coloana + pos[i].coloana;
			aux.linie = a[k - 1].linie + pos[i].linie;
			if (acceptabil(aux)) {
				a[k] = aux;
				matrice[a[k].linie][a[k].coloana] = 2; 
				labirint(k + 1);     
			}
		}
	}
}  

int explorare() {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matrice[i][j] == 1) {
				counter++;
				matrice[i][j] = 2;
				a[0].linie = i;
				a[0].coloana = j;
				labirint(1);
			}
		}
	}
	return counter;
}



int main(void)
{
	initializare();
	int counter = 0;
	counter = explorare();
	printf("Nr de obiecte:%d\n", counter);
	return 0;
}