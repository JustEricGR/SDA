#pragma once

#include<stdio.h>

#define Type int

typedef struct nod {
	Type val;
	struct nod* urm;
}nod;

typedef struct {
	nod* prim;
	nod* ultim;
}Lista;

void lista_init(Lista* lista);
nod* nod_nou(Type n);
void append(Lista* l, Type nr);
void stergere(Lista* l, Type nr);
void add_before(Lista* l, Type before, Type nr);
void add_after(Lista* l, Type after, Type nr);
void afisare(Lista l);
void eliberare(Lista* l);