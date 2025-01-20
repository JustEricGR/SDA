#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct produs {
	int cod;
	struct produs* urm;
}produs;

typedef struct Magazin {
	produs* prim;
	produs* ultim;
	char nume[20];
	struct Magazin* urm;
}Magazin;

typedef struct {
	Magazin* prim;
	Magazin* ultim;
}Magazine;

void magazin_init(Magazin* m) {
	m->prim = m->ultim = NULL;
	m->urm = NULL;
}

void magazine_init(Magazine* m) {
	m->prim = m->ultim = NULL;
}

produs* produs_nou(int cod) {
	produs* e = (produs*)malloc(sizeof(produs));
	if (e == NULL) {
		printf("Eroare la aloxare\n");
		perror(NULL);
		exit(-1);
	}
	e->cod = cod;
	e->urm = NULL;

	return e;
}

Magazin* magazin_nou(char nume[20]) {
	Magazin* e = (Magazin*)malloc(sizeof(Magazin));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	magazin_init(e);
	strcpy(e->nume, nume);

	return e;
}

void adaugaProdus(Magazin* m, int cod) {
	if (m->prim == NULL) {
		m->prim = m->ultim = produs_nou(cod);
	}
	else {
		produs* aux = produs_nou(cod);
		m->ultim->urm = aux;
		m->ultim = aux;
	}
}

void adaugaMagazin(Magazine* m, Magazin *m1) {
	if (m->prim == NULL) {
		m->prim = m->ultim = m1;
	}
	else {
		m->ultim->urm = m1;
		m->ultim = m1;
	}
}

void afisareMagazin(Magazin* m) {
	for (produs* p = m->prim; p != NULL; p = p->urm) {
		printf("%d ", p->cod);
	}printf("\n");
}

void afisareMagazine(Magazine* m) {
	for (Magazin* m1 = m->prim; m1 != NULL; m1 = m1->urm) {
		puts(m1->nume);
		afisareMagazin(m1);
	}
}

void eliberareMagazin(Magazin* m) {
	produs* c = m->prim;
	while (c != NULL) {
		produs* aux = c->urm;
		free(c);
		c = aux;
	}
}

void eliberareMagazine(Magazine* m) {
	Magazin* m1 = m->prim;
	while (m1 != NULL) {
		Magazin* aux = m1->urm;
		eliberareMagazin(m1);
		free(m1);
		m1 = aux;
	}
}

void stergere(Magazin* m, int cod) {
	if (m->prim->cod == cod) {
		produs* aux = m->prim->urm;
		free(m->prim);
		m->prim = aux;
	}
	else if (m->ultim->cod == cod) {
		produs* aux = m->prim;
		for(;aux->urm!=m->ultim;aux=aux->urm) {}
		aux->urm = NULL;
		free(m->ultim);
		m->ultim = aux;
	}
	else {
		produs* c = m->prim;
		produs* p = NULL;
		for (; c != NULL; p = c, c = c->urm) {
			if (c->cod == cod) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void stergereProd(Magazine* m, int cod) {
	for (Magazin* m1 = m->prim; m1 != NULL; m1 = m1->urm) {
		stergere(m1, cod);
	}
}

int main(void) {
	Magazine m;
	magazine_init(&m);

	Magazin* m1 = NULL, * m2 = NULL, * m3 = NULL;
	m1 = magazin_nou("mag1");
	m2 = magazin_nou("mag2");
	m3 = magazin_nou("mag3");

	for (int i = 0; i < 3; i++) {
		adaugaProdus(m1, i);
	}

	for (int i = 0; i < 3; i++) {
		adaugaProdus(m2, i*2);
	}

	for (int i = 0; i < 3; i++) {
		adaugaProdus(m3, i*3);
	}

	adaugaMagazin(&m, m1);
	adaugaMagazin(&m, m2);
	adaugaMagazin(&m, m3);

	afisareMagazine(&m);


	printf("Dupa stergere:\n");
	stergereProd(&m, 0);
	afisareMagazine(&m);

	eliberareMagazine(&m);
}