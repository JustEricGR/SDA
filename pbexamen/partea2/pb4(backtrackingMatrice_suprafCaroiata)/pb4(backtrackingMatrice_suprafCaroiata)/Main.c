#include <stdio.h>
#define N 4

typedef struct coordonate
{
	int linie, coloana;
}coordonate;
coordonate pos[4];
coordonate a[N * N];
int matrice[N][N] = { 0,0,0,0,
				   0,0,0,0,
				   0,0,0,0,
				   0,0,0,0 };

int culori[4] = { 1,2,3,4 };

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

int marker() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matrice[i][j] == 0)return 0;
		}
	}
	return 1;
}

void clear() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrice[i][j] = 0;
		}
	}
}
int solutie()
{
	return marker();
}
int acceptabil(coordonate c)
{
	if (matrice[c.linie][c.coloana] == 0 && c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N) //daca este liber si coordonata se afla in dimensiunile matricei
		return 1;
	else return 0;
}

int verificare_diagonala(coordonate c) {
	//stanga sus
	for()
}

void afiseaza_solutia(k)
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
void labirint(int k)  //k pasul, c coordonata curenta
{
	int i; coordonate aux;
	if (solutie(k)) {
		afiseaza_solutia(k);
		//clear();
	}
	else
	{
		for (int j = 0; j < 4; j++) {
			matrice[a[k - 1].linie][a[k - 1].coloana] = culori[j];
			afiseaza_solutia(k);
			for (i = 0; i < 4; i++)  // parcurgem pe rand posibilitatile
			{
				aux.coloana = a[k - 1].coloana + pos[i].coloana;
				aux.linie = a[k - 1].linie + pos[i].linie;
				if (acceptabil(aux)) {//daca posibilitatea  e acceptabila
					//printf("Intrare in acceptabil\n");
					a[k] = aux;
					//int n = matrice[a[k].linie][a[k].coloana];
					//matrice[a[k].linie][a[k].coloana] = 2; //marcheaza ca vizitat
					labirint(k + 1);     // back1(posibilitate_k+1)
					matrice[a[k].linie][a[k].coloana] = 0; //sterge marcajul ca vizitat
				}
			}
		}
	}
}   /*labirint*/

int main(void)
{
	initializare();
	a[0].linie = 0;
	a[0].coloana = 0;
	
	//matrice[a[0].linie][a[0].coloana] = 2; //marchez ca vizitat
	labirint(1);
	return 0;
}