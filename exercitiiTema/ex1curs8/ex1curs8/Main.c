#include "List.h"

int main(void) {
	Lista l;
	lista_init(&l);
	append(&l, 10);
	append(&l, 20);
	append(&l, 30);
	append(&l, 40);

	afisare(l);

	add_before(&l, 10, 5);
	add_after(&l, 30, 35);
	stergere(&l, 20);
	afisare(l);

	eliberare(&l);
}