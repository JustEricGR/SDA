#include "List.h"
#include<stdlib.h>

void lista_init(Lista* lista) {
	lista->prim = lista->ultim = NULL;
}

nod* nod_nou(Type n) {
	nod* e = (nod*)malloc(sizeof(nod));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->val = n;
	e->urm = NULL;
	return e;
}

void append(Lista* l, Type nr) {
	nod* n = nod_nou(nr);
	if (l->prim == NULL) {
		l->prim = l->ultim = n;
	}
	else {
		l->ultim->urm = n;
		l->ultim = n;
	}
}

void stergere(Lista* l, Type nr) {


	if (l->prim->val == nr) {
		nod* aux = l->prim->urm;
		free(l->prim);
		l->prim = aux;
	}
	else if (l->ultim->val == nr) {
		nod* aux = l->prim;
		for (; aux->urm->urm != NULL; aux = aux->urm)
		{
		}
		aux->urm = NULL;
		free(l->ultim);
		l->ultim = aux;
	}
	else {
		nod* c = NULL;
		nod* p = NULL;
		for (c = l->prim; c != NULL; p = c, c = c->urm) {
			if (c->val == nr) {
				p->urm = c->urm;
				free(c);
				c = p->urm;
			}
		}
	}


}

void add_before(Lista* l, Type before, Type nr) {
	if (l->prim->val == before) {
		nod* n = nod_nou(nr);
		n->urm = l->prim;
		l->prim = n;
	}
	else {
		nod* c = l->prim;
		nod* p = NULL;
		for (; c != NULL; p = c, c = c->urm) {
			if (c->val == before) {
				nod* n = nod_nou(nr);
				p->urm = n;
				n->urm = c;
				break;
			}
		}
	}


}

void add_after(Lista* l, Type after, Type nr) {
	if (l->ultim->val == after) {
		nod* n = nod_nou(nr);
		l->ultim->urm = n;
		l->ultim = n;
	}
	else {
		nod* c = l->prim;
		
		for (; c != NULL; c = c->urm) {
			if (c->val == after) {
				nod* n = nod_nou(nr);
				n->urm = c->urm;
				c->urm = n;
				break;
			}
		}
	}


}



void afisare(Lista l) {
	nod* c = l.prim;
	for (; c != NULL; c = c->urm) {
		printf("%d ", c->val);
	}printf("\n");
}

void eliberare(Lista* l) {
	nod* p = l->prim;
	nod* aux = NULL;
	while (p) {
		aux = p->urm;
		free(p);
		p = aux;
	}
}