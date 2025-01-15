#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct student {
	char nume[30];
	struct student* urm;
}student;

typedef struct Conferinta {
	student* prim;
	student* ultim;
	char id[8];
	char parola[10];
	struct Conferinta* urm;
}Conferinta;

typedef struct {
	Conferinta* prim;
	Conferinta* ultim;
}Conferinte;

void conferinta_init(Conferinta* conf) {
	conf->prim = conf->ultim = NULL;
	conf->urm = NULL;
}

void conferinte_init(Conferinte* conf) {
	conf->prim = conf->ultim = NULL;
	
}

student* student_nou(char nume[30]) {
	student* e = (student*)malloc(sizeof(student));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	strcpy(e->nume, nume);
	e->urm = NULL;
	return e;
}

Conferinta* conferinta_noua(char id[8], char parola[10]) {
	Conferinta* e = (Conferinta*)malloc(sizeof(Conferinta));
	if (e == NULL) {
		printf("Eroare la alocare\n");
		perror(NULL);
		exit(-1);
	}
	conferinta_init(e);
	strcpy(e->id, id);
	strcpy(e->parola, parola);
	
	return e;
}

void adaugaStudent(Conferinta* conf, char nume[30]) {
	if (conf->prim == NULL) {
		conf->prim = conf->ultim = student_nou(nume);
	}
	else {
		student* aux = student_nou(nume);
		if (strcmp(conf->prim->nume, nume) > 0) {
			aux->urm = conf->prim;
			conf->prim = aux;
		}
		else {
			student* c = conf->prim->urm;
			student* p = conf->prim;
			int flag = 0;
			for (; c != NULL; p = c, c = c->urm) {
				if (strcmp(c->nume, nume) > 0) {
					p->urm = aux;
					aux->urm = c;
					flag = 1;
					break;
				}
			}
			if (!flag) {
				conf->ultim->urm = aux;
				conf->ultim = aux;
			}
		}
	}
}

void adaugaConferinta(Conferinte* conf, Conferinta* conf1) {
	if (conf->prim == NULL) {
		conf->prim = conf->ultim = conf1;
	}
	else {
		conf->ultim->urm = conf1;
		conf->ultim = conf1;
	}
}

void afisareConferinta(Conferinta* conf) {
	for (student* c = conf->prim; c != NULL; c = c->urm) {
		printf("%s ", c->nume);
	}printf("\n");
}

void afisareConferinte(Conferinte* conf) {
	for (Conferinta* conf1 = conf->prim; conf1 != NULL; conf1 = conf1->urm) {
		printf("ID:%s Parola:%s\n", conf1->id, conf1->parola);
		afisareConferinta(conf1);
	}
}

void eliberareConferinta(Conferinta* conf) {
	student* c = conf->prim;
	while (c != NULL) {
		student* aux = c->urm;
		free(c);
		c = aux;
	}
}

void eliberareConferinte(Conferinte* conf) {
	Conferinta* conf1 = conf->prim;
	while (conf1 != NULL) {
		Conferinta* aux = conf1->urm;
		eliberareConferinta(conf1);
		free(conf1);
		conf1 = aux;
	}
}

void stergere(Conferinta* conf, char nume[30]) {
	if (!strcmp(conf->prim->nume, nume)) {
		student* aux = conf->prim->urm;
		free(conf->prim);
		conf->prim = aux;
	}
	else if (!strcmp(conf->ultim->nume, nume)) {
		student* aux = conf->prim;
		for (; aux->urm != conf->ultim; aux = aux->urm) {}
		aux->urm = NULL;
		free(conf->ultim);
		conf->ultim = aux;
		
	}
	else {
		student* c = conf->prim;
		student* p = NULL;
		for (; c != NULL; p=c, c = c->urm) {
			if (!strcmp(c->nume, nume)) {
				p->urm = c->urm;
				free(c);
				c = p;
			}
		}
	}
}

int main(void) {
	Conferinte conferinte;
	conferinte_init(&conferinte);

	char* nume[] = {
	"Ion Popescu", "Maria Ionescu", "Alex Dumitru", "Elena Georgescu", "Vlad Mihai",
	"Ana Vasile", "Cristian Iordache", "Daniela Marin", "Florin Petrescu", "Gabriela Enache",
	"Radu Stancu", "Irina Preda", "Mihai Ciobanu", "Simona Tudor", "Carmen Roman",
	"Victor Pavel", "Lavinia Dragomir", "Andrei Grigore", "Oana Neagu", "Ioana Barbu",
	"George Voicu", "Monica Tanase", "Bogdan Petrica", "Teodora Filip", "Alexandra Dinu",
	"Robert Stoica", "Bianca Popa", "Adrian Lungu", "Sofia Moldovan", "Paul Ene"
	};

	char* iduri[] = {
		"12345", "67890", "11223", "33445", "55678",
		"99887", "44556", "77889", "99001", "22334",
		"66554", "88123", "44122", "33556", "77441"
	};

	char* parole[] = {
		"abc123", "def456", "ghi789", "jkl012", "mno345",
		"pqr678", "stu901", "vwx234", "yz1234", "abc678",
		"def901", "ghi234", "jkl567", "mno890", "pqr123"
	};

	Conferinta* waitingRoom = NULL;
	waitingRoom = conferinta_noua("12345", "abc123");

	for (int i = 0; i < 30; i++) {
		adaugaStudent(waitingRoom, nume[i]);
	}

	

	Conferinta* conf1 = NULL, * conf2 = NULL, * conf3 = NULL;
	conf1 = conferinta_noua("conf1", parole[4]);
	conf2 = conferinta_noua("conf2", parole[2]);
	conf3 = conferinta_noua("conf3", parole[12]);

	Conferinta *cnf[3] = { conf1,conf2,conf3 };
	srand(time(NULL));
	for (student* s = waitingRoom->prim; s != NULL; s = s->urm) {
		if (strchr("aeiouAEIOU", s->nume[0])) {
			
			adaugaStudent(cnf[rand() % 3], s->nume);
			if (!strcmp(waitingRoom->prim->nume, s->nume)) {
				student* aux = waitingRoom->prim->urm;
				free(waitingRoom->prim);
				waitingRoom->prim = aux;
				s = waitingRoom->prim;
			}
			else if (!strcmp(waitingRoom->ultim->nume, s->nume)) {
				student* aux = waitingRoom->prim;
				for (; aux->urm != waitingRoom->ultim; aux = aux->urm) {}
				aux->urm = NULL;
				free(waitingRoom->ultim);
				waitingRoom->ultim = aux;
				s = waitingRoom->ultim;

			}
			else {
				student* c = waitingRoom->prim;
				student* p = NULL;
				for (; c != NULL; p = c, c = c->urm) {
					if (!strcmp(c->nume, s->nume)) {
						p->urm = c->urm;
						free(c);
						c = p;
						s = c;
					}
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		adaugaConferinta(&conferinte, cnf[i]);
	}

	afisareConferinte(&conferinte);

	printf("Waiting Room:\n");
	afisareConferinta(waitingRoom);

	eliberareConferinte(&conferinte);

}

