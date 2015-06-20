#ifndef TIPOVI
#define TIPOVI
#include <math.h>


typedef struct cv{

	struct cv *gore, *dole, *levo, *desno;
	int posecen;

	int i, j;
	int stepen_veze;
	int vlasnik;
	int tip;
	int seen, vidjen;

}Cvor;

typedef struct el{

	Cvor *pokCvor;
	struct el *sledeci;

}Niz_t;

typedef struct sk{

	Cvor *element;
	struct sk *sledeci;

}skup_pravougaonik_t;

typedef struct{

	int x1, x2, y1, y2;

}koordinate;

typedef struct{

	skup_pravougaonik_t *prvi, *sansa;

}zajedno;

#endif