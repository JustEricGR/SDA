#include<stdio.h>
#include<stdlib.h>

typedef struct nod {
	int n;
	struct nod* urm;
}nod;

typedef struct {
	nod* prim;
	nod* ultim;
}Lista;

void lista_init(Lista* l) {
	l->prim = l->ultim = NULL;
}

nod* nod_nou(int n) {
	nod* e = (nod*)malloc(sizeof(nod));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->urm = NULL;
	e->n = n;

	return e;
}

void append(Lista* l, int n, int *size) {
	if (l->prim == NULL) {
		l->prim = l->ultim = nod_nou(n);
	}
	else {
		nod* aux = nod_nou(n);
		l->ultim->urm = aux;
		l->ultim = aux;
	}
	*size += 1;
}

void afisare(Lista l) {
	for (nod* c = l.prim; c != NULL; c = c->urm) {
		printf("%d ", c->n);
	}printf("\n");
}

void eliberare(Lista* l) {
	nod* c = l->prim;
	while (c != NULL) {
		nod* aux = c->urm;
		free(c);
		c = aux;
	}
}

void stergere_mijloc(Lista* l, int size) {
	nod* c = l->prim;
	nod* p = c;
	int flag = 0;
	for (; c != NULL;p=c,c=c->urm) {
		
		if (flag == (size / 2)) {
			p->urm = c->urm;
			free(c);
			c = p;
		}
		flag++;
	}
	
}

int main(void) {
	Lista l;
	lista_init(&l);
	int size = 0;
	
	for (int i = 1; i <= 7; i++) {
		append(&l, i, &size);
	}

	afisare(l);
	//printf("Nr noduri:%d\n", size);

	printf("Dupa stergerea elementului din mijloc:\n");
	stergere_mijloc(&l, size);
	afisare(l);

	eliberare(&l);
}