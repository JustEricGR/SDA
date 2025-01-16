#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct proces {
	char nume[10];
	int prioritate;
	struct proces* urm;
}proces;

typedef struct Lista {
	char nume[10];
	int prioritate;
	struct Lista* urm;
	proces* prim;
	proces* ultim;
}Lista;

typedef struct Multilista {
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

proces* proces_nou(char nume[10], int prioritate) {
	proces* e = (proces*)malloc(sizeof(proces));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(e->nume, nume);
	e->prioritate = prioritate;
	e->urm = NULL;

	return e;
}

Lista* lista_noua(char nume[10], int prioritate) {
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

void adaugaProces(Lista* l, char nume[10], int prioritate) {
	if (l->prim == NULL) {
		l->prim = l->ultim = proces_nou(nume, prioritate);
	}
	else {
		proces* aux = proces_nou(nume, prioritate);
		l->ultim->urm = aux;
		l->ultim = aux;
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
		printf("Nume:%s - prioritate:%d; ", p->nume, p->prioritate);
	}printf("\n");
}

void afisareMultilista(Multilista* m) {
	for (Lista* l = m->prim; l != NULL; l = l->urm) {
		printf("Nume:%s - prioritate:%d\n", l->nume, l->prioritate);
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
	Lista* l = m->prim;;
	while (l != NULL) {
		Lista* aux = l->urm;
		eliberareLista(l);
		free(l);
		l = aux;
	}
}

//proces* stergerePrim(Lista* l) {
//	proces* returnat = l->prim;
//	returnat->urm = NULL;
//	proces* aux = l->prim->urm;
//	free(l->prim);
//	l->prim = aux;
//	return returnat;
//}

void mutare(Multilista* m, Lista* l) {
	//proces* p = l->prim;
	while (l->prim != NULL) {
		proces* returnat = proces_nou(l->prim->nume, l->prim->prioritate);
		//returnat->urm = NULL;
		proces* aux = l->prim->urm;
		free(l->prim);
		l->prim = aux;
		for (Lista* l = m->prim; l != NULL; l = l->urm) {
			if (l->prioritate == returnat->prioritate) {
				adaugaProces(l, returnat->nume, returnat->prioritate);
				break;
			}
		}
	}
}

int main(void) {
	Multilista multilista;
	multilista_init(&multilista);

	Lista* liste[8];
	Lista* stiva=NULL;
	stiva = lista_noua("stiva", 0);

	adaugaProces(stiva, "proces100", 3);
	adaugaProces(stiva, "proces200", 7);
	adaugaProces(stiva, "proces300", 2);

	for (int i = 0; i < 8; i++) {
		liste[i] = NULL;
	}

	
	char n[10] = "Lista";
	for (int i = 0; i < 8; i++) {
		char aux[10] = "";
		sprintf(aux, "%s%d", n, i + 1);
		liste[i] = lista_noua(aux, i + 1);
		//afisareLista(liste[i]);
	}

	int counter = 1;
	char pr[10] = "proces";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			char aux[10] = "";
			sprintf(aux, "%s%d", pr, counter);
			adaugaProces(liste[i], aux, liste[i]->prioritate);
		}
		//afisareLista(liste[i]);
	}

	for (int i = 0; i < 8; i++) {
		adaugaLista(&multilista, liste[i]);
	}

	afisareMultilista(&multilista);

	printf("Dupa mutare:\n");
	mutare(&multilista, stiva);
	afisareMultilista(&multilista);
	

	eliberareMultilista(&multilista);
}

