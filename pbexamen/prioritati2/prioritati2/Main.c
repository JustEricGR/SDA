#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct proces {
	int prioritate;
	char nume[15];
	struct proces* urm;
}proces;

typedef struct Lista {
	int prioritate;
	char nume[15];
	proces* prim;
	proces* ultim;
	struct Lista* urm;
}Lista;

typedef struct {
	Lista* prim;
	Lista* ultim;
}Multilista;

void lista_init(Lista* l) {
	l->prim = l->ultim = NULL;
	l->urm = NULL;
}

void multilista_init(Multilista* m) {
	m->prim = m->ultim = NULL;
}

proces* proces_nou(int prioritate, char nume[15]) {
	proces* e = (proces*)malloc(sizeof(proces));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(e->nume, nume);
	e->prioritate = prioritate;

	return e;
}

Lista* lista_noua(int prioritate, char nume[15]) {
	Lista* e = (Lista*)malloc(sizeof(Lista));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	lista_init(e);
	strcpy(e->nume, nume);
	e->prioritate = prioritate;

	return e;
}

void adaugaProces(Lista* l, char nume[15], int prioritate) {
	if (l->prim == NULL) {
		l->prim = l->ultim = proces_nou(prioritate, nume);
	}
	else {
		proces *aux= proces_nou(prioritate, nume);
		l->ultim->urm = aux;
		l->ultim = aux;
		l->ultim->urm = NULL;
	}
}

void adaugaLista(Multilista* m, Lista* l) {
	if (m->prim == NULL) {
		m->prim = m->ultim = l;
	}
	else {
		
		m->ultim->urm = l;
		m->ultim = l;
	}
}

void afisareLista(Lista* l) {
	for (proces* p = l->prim; p != NULL; p = p->urm) {
		printf("%s - %d;  ", p->nume, p->prioritate);
	}printf("\n");
}

void afisareMultilista(Multilista* m) {
	for (Lista* l = m->prim; l != NULL; l = l->urm) {
		printf("%s - %d\n", l->nume, l->prioritate);
		afisareLista(l);
	}
}

void eliberareLista(Lista* l) {
	proces* c = l->prim;
	while (c != NULL) {
		proces* aux = c->urm;
		free(c);
		c = aux;
	}
}

void eliberareMultilista(Multilista* m) {
	Lista* c = m->prim;
	while (c != NULL) {
		Lista* aux = c->urm;
		eliberareLista(c);
		free(c);
		c = aux;
	}
}

void scos_si_adaugat(Multilista* m, Lista* l) {
	//proces* p = l->prim;
	while (l->ultim != NULL) {
		
		if (l->prim == l->ultim) {
			for (Lista* l1 = m->prim; l1 != NULL; l1 = l1->urm) {
				if (l1->prioritate == l->prim->prioritate) {
					adaugaProces(l1, l->ultim->nume, l->ultim->prioritate);
					break;
				}
			}
			//eliberareLista(l);
			free(l->prim);
			l->prim = l->ultim = NULL;
			
		} 
		
		else {
			proces* aux = l->prim;
			for (; aux->urm != l->ultim; aux = aux->urm) {
				//printf("%s - %d;  ", aux->nume, aux->prioritate);
			}/*printf("\n")*/;
			//p->urm = NULL;
			for (Lista* l1 = m->prim; l1 != NULL; l1 = l1->urm) {
				if (l1->prioritate == l->ultim->prioritate) {
					adaugaProces(l1, l->ultim->nume, l->ultim->prioritate);
					break;
				}
			}
			free(l->ultim);
			l->ultim = aux;
			l->ultim->urm = NULL;
		}
	}
}

int main(void) {
	Multilista m;
	multilista_init(&m);
	Lista* liste[9];
	char name[15] = "Lista";
	for (int i = 0; i < 9; i++) {
		char nume[15] = "";
		sprintf(nume, "%s%d", name, i);
		liste[i] = lista_noua(i, nume);
		adaugaLista(&m, liste[i]);
	}

	Lista* stiva = NULL;
	stiva=lista_noua(10, "stiva");

	char aux[15] = "proces";
	for (int i = 0; i < 30; i++) {
		char aux1[15] = "";
		sprintf(aux1, "%s%d", aux, i);
		adaugaProces(stiva, aux1, i % 9);
	}

	//afisareLista(stiva);

	scos_si_adaugat(&m, stiva);

	afisareMultilista(&m);

	eliberareMultilista(&m);
	
}