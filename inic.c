#include "tipovi.h"
#include <stdlib.h>
#include <time.h>


/*funkcija inicijalizuje glavnu strukturu koja ce se koristiti za sve faze kompjuterske igre*/
Cvor *kreiranje_polja_p(int m, int n){
	int i, j;
	Cvor *novi, *b, *pomocna, *a;


	a=(Cvor*)malloc((m+2)*(n+2)*sizeof(Cvor));
	if (a==NULL) exit(1);
	pomocna=a;

	for (i=0; i<m+2; i++) {
		for (j=0; j<n+2; j++) {
			if (i==0 && j==0) continue;
			if (i==0 && j==n+1) continue;
			if (i==m+1 && j==0) continue;
			if (i==m+1 && j==n+1) continue;

			if ((i==0) || (j==0) || (j==n+1) || (i==n+1)){
				pomocna[i*n+j].vlasnik=0;
				pomocna[i*n+j].stepen_veze=1;
				pomocna[i*n+j].tip=0;
				if (i==0) {
					pomocna[i*n+j].dole=&pomocna[(i+1)*n+j];
					pomocna[i*n+j].levo=pomocna[i*n+j].gore=pomocna[i*n+j].desno=NULL;
				}
				if (j==0) {
					pomocna[i*n+j].desno=&pomocna[i*n+j+1];
					pomocna[i*n+j].levo=pomocna[i*n+j].gore=pomocna[i*n+j].dole=NULL;
				}
				if (j==n+1) {
					pomocna[i*n+j].levo=&pomocna[i*n+j-1];
					pomocna[i*n+j].desno=pomocna[i*n+j].gore=pomocna[i*n+j].dole=NULL;
				}
				if (i==m+1) {
					pomocna[i*n+j].gore=&pomocna[(i-1)*n+j];
					pomocna[i*n+j].levo=pomocna[i*n+j].gore=pomocna[i*n+j].desno=NULL;
				}
			}else{
				pomocna[i*n+j].vlasnik=0;
				pomocna[i*n+j].stepen_veze=4;
				pomocna[i*n+j].tip=1;
			
				pomocna[i*n+j].gore=&pomocna[(i-1)*n+j];
				pomocna[i*n+j].dole=&pomocna[(i+1)*n+j];
				pomocna[i*n+j].desno=&pomocna[i+n+j+1];
				pomocna[i*n+j].levo=&pomocna[i*n+j-1];
			}
		}
	}
	return pomocna;
}


/*ova funkcija inicijalizuje strukturu koja sluzi za vodjenje evidencije koliko ima kutijica sa odredjenim brojem kompletiranih crtica oko nje*/
Niz_zaglavlje_t *pravljenje_EVNp(Cvor *pomocna, int n, int m){
		Niz_zaglavlje_t niz[5];
		Niz_t *novi, *prethodni, *pom;

		int i, j;

		niz[1].pokPrvi->sledeci=niz[2].pokPrvi->sledeci=niz[3].pokPrvi->sledeci=niz[4].pokPrvi->sledeci=NULL;
		niz[1].br_el=niz[2].br_el=niz[3].br_el=niz[4].br_el=0;

		niz[0].br_el=n*m;

		niz[0].pokPrvi->sledeci=NULL;
		
		for (i=1; i<=m; i++) {
			for (j=1; j<=n; j++) {
				pom=(Niz_t *) malloc(sizeof(Niz_t));
				if (pom==NULL){
					exit(2);
				}
				novi=pom;
				novi->pokCvor=pomocna[i][j];
				novi->sledeci=NULL;
				if (niz[0].pokPrvi->sledeci==NULL) {
					niz[0].pokPrvi->sledeci=novi;
					prethodni=novi;
				}else{
					prethodni->sledeci=novi;
					prethodni=novi;
				}
			}
		}

		return niz;
}



/*Ovaj funkcija sluzi za pracenje trenutne situacije, gde moze da se igra, da li se igra prva ili druga faza, 
u sustini u njoj se cuvaju pozicije gde je jos uvek moguce igrati(cuvaju se samo dostupni elementi, sa 1 ili dve crtice formirane)*/
skup_t *inic_skup(Niz_zaglavlje_t *niz){
	Niz_t *tekuci;
	skup_t *pomocni, *prethodni, *novi, *prvi;

	prvi=NULL;

	while (tekuci){
		pomocni=(skup_t*)malloc(sizeof(skup_t));
		if (pomocni==NULL) exit(2);
		novi=pomocni;
		novi->element=tekuci->pokCvor;
		novi->sledeci=NULL;
		if (prvi==NULL){
			prvi=novi;
			prethodni=novi;
		}else{
			prethodni->sledeci=novi;
			prethodni=novi;
		}		
		tekuci=tekuci->sledeci;
	}

	return prvi;
}


/*Nalazi slucajni element od dostupnih*/
skup_t *setanje(skup_t *prvi_s, int x){
	skup_t *tekuci=prvi_s;

	while (x) {
		tekuci=tekuci->sledeci;
		if (tekuci==NULL) {
			tekuci=prvi_s;
		}
		--x;
	}

	return tekuci;
}

/*brise element za koji je prethodno odredjeno da vise ne moze da se odigra na njegovo mesto*/
skup_t *brisanje(skup_t *prvi_s, skup_t *element){
	skup_t *prethodni=prvi_s;
	
	if (prvi_s==element){
		prvi_s=prvi_s->sledeci;
		free(element);
	}else{
		while (prethodni->sledeci!=element) {
			prethodni=prethodni->sledeci;
		}
		prethodni->sledeci=element->sledeci;
		free(element);
	}

	return prvi_s;

}

/*samo nakon f1 poteza*/
skup_t *azuriranje_skupova(skup_t *prvi_s, skup_t *node){

	if (node->element->stepen_veze == 2){
		prvi_s=brisanje(prvi_s,node);
	}

	return prvi_s;
}