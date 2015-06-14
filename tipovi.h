typedef struct cv{ 
	
	struct cv *gore, *dole, *levo, *desno;
	int posecen;

	int stepen_veze;
	int vlasnik;
	int tip;

}Cvor;

typedef struct el{

	Cvor *pokCvor;
	struct el *sledeci;

}Niz_t;

typedef struct elm{
	
	int br_el;
	Niz_t *pokPrvi;

}Niz_zaglavlje_t;

typedef struct sk{

	Cvor *element;
	struct sk *sledeci;

}skup_t;
