#include "List.h"

int numarare_recursiva(nod *n) {
	
	if (n == NULL) 
		return 0;
	
	else return 1 + numarare_recursiva(n->urm);
}

int main(void) {
	Lista l;
	lista_init(&l);
	append(&l, 10);
	append(&l, 20);
	append(&l, 30);
	append(&l, 40);

	afisare(l);

	printf("Sunt %d noduri\n", numarare_recursiva(l.prim));

	

	eliberare(&l);
}