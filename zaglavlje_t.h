#include <stdio.h>
#include <stdlib.h>

typedef struct cv_t{
	
	struct cv_t *osnova, *levo, *desno;

	int stepen_veze;
	int vlasnik;
	int tip;

}Cv_t;

typedef struct skup{
	
	Cv_t *element;
	struct skup *sledeci;

}skup_trougao_t;
