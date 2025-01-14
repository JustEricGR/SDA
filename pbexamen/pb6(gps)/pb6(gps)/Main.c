#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct gps {
	int cod;
	struct gps* urm;
}gps;

typedef struct Firma {
	gps* prim;
	gps* ultim;
	struct Firma* urm;
	char nume[20];
}Firma;

typedef struct {
	Firma* prim;
	Firma* ultim;
}Firme;

void firma_init(Firma* f) {
	f->prim = f->ultim = NULL;
	f->urm = NULL;
}

void firme_init(Firme* f) {
	f->prim = f->ultim = NULL;
}

gps* gps_nou(int cod) {
	gps* e = (gps*)malloc(sizeof(gps));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->cod = cod;
	e->urm = NULL;
	return e;
}

Firma* firma_noua(char nume[20]) {
	Firma* e = (Firma*)malloc(sizeof(Firma));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(e->nume, nume);
	firma_init(e);
	return e;
}

void adaugaGps(Firma* f, int cod) {
	if (f->prim == NULL) {
		f->prim = f->ultim = gps_nou(cod);
	}
	else {
		gps* aux = gps_nou(cod);
		if (f->prim > cod) {
			aux->urm = f->prim;
			f->prim = aux;
		}
		else {
			gps* c = f->prim->urm;
			gps* p = f->prim;
			int flag = 0;
			for (; c != NULL; p = c, c = c->urm) {
				if (c->cod > cod) {
					aux->urm = c;
					p->urm = aux;
					flag = 1;
					break;
				}
			}
			if (!flag) {
				f->ultim->urm = aux;
				f->ultim = aux;
			}
		}
	}
}

void adaugaFirma(Firma* f1, Firme* f) {
	if (f->prim == NULL) {
		f->prim = f->ultim = f1;
	}
	else {
		f->ultim->urm = f1;
		f->ultim = f1;
	}
}

void afisareFirma(Firma* f) {
	for (gps* g = f->prim; g != NULL; g = g->urm) {
		printf("%d ", g->cod);
	}printf("\n");
}

void afisareFirme(Firme* f) {
	for (Firma* f1 = f->prim; f1 != NULL; f1 = f1->urm) {
		puts(f1->nume);
		afisareFirma(f1);
	}
}

void eliberareFirma(Firma* f) {
	gps* g = f->prim;
	while (g != NULL) {
		gps* aux = g->urm;
		free(g);
		g = aux;
	}
}

void eliberareFirme(Firme* f) {
	Firma* f1 = f->prim;
	while (f1 != NULL) {
		Firma* aux = f1->urm;
		eliberareFirma(f1);
		free(f1);
		f1 = aux;
	}
}

void stergeGps(Firma* f, int cod) {
	if (f->prim->cod == cod) {
		gps* aux = f->prim->urm;
		free(f->prim);
		f->prim = aux;
	}
	else if(f->ultim->cod == cod) {
		gps* c = f->prim;
		for(;c->urm!=f->ultim;c=c->urm) {}
		c->urm = NULL;
		free(f->ultim);
		f->ultim = c;
	}
	else {
		gps* c = f->prim;
		gps* p = NULL;
		for (; c != NULL; p = c, c = c->urm) {
			if (c->cod == cod) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

void eliminaGps(Firme* f, int cod) {
	for (Firma* f1 = f->prim; f1 != NULL; f1 = f1->urm) {
		stergeGps(f1, cod);
	}
}

int main(void) {
	Firme firme;
	firme_init(&firme);

	Firma* f1 = NULL, * f2 = NULL, * f3 = NULL;
	f1 = firma_noua("Firma1");
	f2 = firma_noua("Firma2");
	f3 = firma_noua("Firma3");

	for (int i = 6; i > 0; i--) {
		adaugaGps(f1, i);
	}

	for (int i = 6; i > 0; i--) {
		adaugaGps(f2, i*2);
	}

	for (int i = 6; i > 0; i--) {
		adaugaGps(f3, i*3);
	}

	adaugaFirma(f1, &firme);
	adaugaFirma(f2, &firme);
	adaugaFirma(f3, &firme);

	afisareFirme(&firme);

	printf("Dupa stergere:\n");
	eliminaGps(&firme, 3);
	afisareFirme(&firme);

	eliberareFirme(&firme);
}