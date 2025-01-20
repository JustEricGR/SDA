#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pasager {
	int cod;
	struct pasager* urm;
}pasager;

typedef struct zbor {
	char nume[15];
	pasager* prim;
	pasager* ultim;
	struct zbor* urm;
}zbor;

typedef struct {
	zbor* prim;
	zbor* ultim;
}zboruri;

void zbor_init(zbor* z) {
	z->prim = z->ultim = NULL;
	z->urm = NULL;
}

void zboruri_init(zboruri* z) {
	z->prim = z->ultim = NULL;
}

pasager* pasager_nou(int cod) {
	pasager* e = (pasager*)malloc(sizeof(pasager));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->cod = cod;
	e->urm = NULL;

	return e;
}

zbor* zbor_nou(char nume[15]) {
	zbor* e = (zbor*)malloc(sizeof(zbor));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	zbor_init(e);
	strcpy(e->nume, nume);

	return e;
}

void adaugarePasager(zbor* z, int cod) {
	if (z->prim == NULL) {
		z->prim = z->ultim = pasager_nou(cod);
	}
	else {
		pasager *aux = pasager_nou(cod);
		z->ultim->urm = aux;
		z->ultim = aux;
	}
}

void adaugareZbor(zboruri* z, zbor* z1) {
	if (z->prim == NULL) {
		z->prim = z->ultim = z1;
	}
	else {
		z->ultim->urm = z1;
		z->ultim = z1;
	}
}

void afisareZbor(zbor* z) {
	for (pasager* p = z->prim; p != NULL; p = p->urm) {
		printf("%d ", p->cod);
	}printf("\n");
}

void afisareZboruri(zboruri* z) {
	for (zbor* z1 = z->prim; z1 != NULL; z1 = z1->urm) {
		puts(z1->nume);
		afisareZbor(z1);
	}
}

void eliberareZbor(zbor* z) {
	pasager* p=z->prim;
	while (p != NULL) {
		pasager* aux = p->urm;
		free(p);
		p = aux;
	}
}

void eliberareZboruri(zboruri* z) {
	zbor* p = z->prim;
	while (p != NULL) {
		pasager* aux = p->urm;
		eliberareZbor(p);
		free(p);
		p = aux;
	}
}

void stergere(zbor* z, int cod) {
	if (z->prim->cod == cod) {
		pasager* aux = z->prim->urm;
		free(z->prim);
		z->prim = aux;
	}
	else if (z->ultim->cod == cod) {
		pasager* aux = z->prim;
		for (; aux->urm != z->ultim; aux = aux->urm) {}
		aux->urm = NULL;
		free(z->ultim);
		z->ultim = aux;
	}
	else {
		pasager* c = z->prim;
		pasager* p = NULL;
		for (; c != NULL; p = c, c = c->urm) {
			if (c->cod == cod) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void stergereTotala(zboruri* z, int cod) {
	for (zbor* z1 = z->prim; z1 != NULL; z1 = z1->urm) {
		stergere(z1, cod);
	}
}

int main(void) {
	zboruri z;
	zboruri_init(&z);

	zbor* z1 = NULL, * z2 = NULL, * z3 = NULL;
	z1 = zbor_nou("zbor1");
	z2 = zbor_nou("zbor2");
	z3 = zbor_nou("zbor3");

	for (int i = 0; i < 10; i++) {
		adaugarePasager(z1, i);
		adaugarePasager(z2, i*2);
		adaugarePasager(z3, i*3);
	}

	adaugareZbor(&z, z1);
	adaugareZbor(&z, z2);
	adaugareZbor(&z, z3);

	afisareZboruri(&z);

	printf("Dupa stergere:\n");
	stergereTotala(&z, 0);
	afisareZboruri(&z);

	eliberareZboruri(&z);
}