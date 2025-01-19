#include<stdio.h>
#include<stdlib.h>

typedef struct Persoana {
	int ID;
	char nume[35];
	char ocupatie[35];
	struct Persoana* urm;
	struct Contacte* contacte;
}Persoana;

typedef struct Contacte {
	Persoana* prim;
	Persoana* ultim;
}Contacte;

typedef struct Persoane {
	Persoana* prim;
	Persoana* ultim;
}Persoane;

void persoane_init(Persoane* p) {
	p->prim = p->ultim = NULL;
}

void contacte_init(Contacte* c) {
	c->prim = c->ultim = NULL;
	//c->prim->urm = c->ultim->urm = NULL;
}

Contacte* contact_nou() {
	Contacte* e = (Contacte*)malloc(sizeof(Contacte));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	contacte_init(e);
	return e;
}

Persoana* persoana_noua(int ID, char nume[35], char ocupatie[35]) {
	Persoana* e = (Persoana*)malloc(sizeof(Persoana));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	e->urm = NULL;
	e->contacte = contact_nou();
	e->ID = ID;
	strcpy(e->nume, nume);
	strcpy(e->ocupatie, ocupatie);

	return e;
}

void adaugareContact(Persoana* nod, int ID, char nume[35], char ocupatie[35]) {
	Persoana* aux = persoana_noua(ID, nume, ocupatie);
	if (nod->contacte->prim == NULL) {
		nod->contacte->prim = nod->contacte->ultim = aux;
	}
	else {

		nod->contacte->ultim->urm = aux;
		nod->contacte->ultim = aux;
	}
}

void adaugarePersoanaInPersoane(Persoane* p, Persoana* p1) {
	if (p->prim == NULL) {
		p->prim = p->ultim = p1;

	}
	else {
		p->ultim->urm = p1;
		p->ultim = p1;
	}
}

void afisareContacte(Contacte* c) {
	printf("Contacte:\n");
	for (Persoana* p = c->prim; p != NULL; p = p->urm) {
		printf("ID: %d; Nume: %s; Ocupatie: %s\n", p->ID, p->nume, p->ocupatie);
	}printf("\n\n");
}

void afisarePersoana(Persoana* p) {
	printf("ID: %d; Nume: %s; Ocupatie: %s\n", p->ID, p->nume, p->ocupatie);
	afisareContacte(p->contacte);
}

void afisarePersoane(Persoane* p) {
	for (Persoana* p1 = p->prim; p1 != NULL; p1 = p1->urm) {
		afisarePersoana(p1);
	}
}

void eliberareContact(Contacte* c) {
	Persoana* p = c->prim;
	while (p != NULL) {
		Persoana* aux = p->urm;
		free(p);
		p = aux;
	}
	free(c);
}

void eliberarePersoane(Persoane* p) {
	Persoana* p1 = p->prim;
	while (p1 != NULL) {
		Persoana* aux = p1->urm;
		eliberareContact(p1->contacte);
		free(p1);
		p1 = aux;
	}
}

void adaugareContactPersoane(Persoane* p, char numeNod[35], int ID, char nume[35], char ocupatie[35]) {
	for (Persoana* p1 = p->prim; p1 != NULL; p1 = p1->urm) {
		if (!strcmp(p1->nume, numeNod)) {
			adaugareContact(p1, ID, nume, ocupatie);
			break;
		}
	}
}

int main(void) {
	Persoane persoane;
	persoane_init(&persoane);

	Persoana* p1 = NULL, * p2 = NULL, * p3 = NULL;

	p1 = persoana_noua(1234, "Ion", "Brutar");
	p2 = persoana_noua(563, "Roxana", "ITist");
	p3 = persoana_noua(27288, "Cristi", "Fotbalist");

	adaugareContact(p1, 1223, "Ana", "Croitoreasa");
	adaugareContact(p1, 3456, "Vasile", "Mester");
	adaugareContact(p1, 23515, "Bogdan", "Electrician");

	adaugareContact(p2, 298715, "Eric", "Boss");
	adaugareContact(p2, 15625, "Cristina", "Economista");
	adaugareContact(p2, 39815, "Andrei", "Nimic");

	adaugareContact(p3, 515097, "Andreea", "Inginera");
	adaugareContact(p3, 87549, "Dragos", "Sef");
	adaugareContact(p3, 76346, "Adrian", "...");

	adaugarePersoanaInPersoane(&persoane, p1);
	adaugarePersoanaInPersoane(&persoane, p2);
	adaugarePersoanaInPersoane(&persoane, p3);

	afisarePersoane(&persoane);

	adaugareContactPersoane(&persoane, "Ion", 53636, "Dani", "tot");
	afisarePersoane(&persoane);

	eliberarePersoane(&persoane);
}