#include <stdio.h>
#define N 4

typedef struct coordonate
{
	int linie, coloana;
}coordonate;
coordonate pos[4];
coordonate a[N * N];
int matrice[N][N] = { -1,-1,-1,-1,
				   -1,0,1,-1,
				   -1,0,0,0,
				   -1,0,-1,0 };




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
int acceptabil(coordonate c, int energie)
{
	if ((matrice[c.linie][c.coloana] == 0 || matrice[c.linie][c.coloana] == 1) && c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N && energie>0) {
		
		return 1;
	}
	//else if (P == 0)return 0;
	else return 0;
}

void afiseaza_solutia(k)
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
void labirint(int k, int precedent, int implicit)  //k pasul, c coordonata curenta
{
	int i; coordonate aux;
	if (solutie(k, a[k - 1])) {
		
		afiseaza_solutia(k);
		
	}
		
	else
	{
		for (i = 0; i < 4; i++)  // parcurgem pe rand posibilitatile
		{
			aux.coloana = a[k - 1].coloana + pos[i].coloana;
			aux.linie = a[k - 1].linie + pos[i].linie;
			if (acceptabil(aux,implicit)) {//daca posibilitatea  e acceptabila
				a[k] = aux;
				int n = matrice[a[k].linie][a[k].coloana];
				int crt = implicit;
				if (n == 0)crt--;
				matrice[a[k].linie][a[k].coloana] = 2; //marcheaza ca vizitat
				labirint(k + 1, n, crt);     // back1(posibilitate_k+1)
				matrice[a[k].linie][a[k].coloana] = n; //sterge marcajul ca vizitat
			}
		}
	}
}   /*labirint*/

int main(void)
{
	int implicit = 2;//puncte de energie
	initializare();
	
	a[0].linie = 1;
	a[0].coloana = 1;
	matrice[a[0].linie][a[0].coloana] = 2; //marchez ca vizitat
	labirint(1,matrice[a[0].linie][a[0].coloana],implicit);
	//afiseaza_solutia();
	return 0;
}

