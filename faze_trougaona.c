#include "funkcije_trougao.h"

skup_trougao_t *zatvaranje_t(skup_trougao_t *dve){
	skup_trougao_t *tek;
	int p, fl=1,i;

	for (p=0; p<2 && fl; p++) {
		switch(p) {
			case 0:
				if (dve->element->osnova!=NULL) {
					fl=0;
					dve->element->osnova=NULL;
					}
				break;
			case 1:
				if (dve->element->desno!=NULL) {
					fl=0;
					dve->element->desno=NULL;
					}
				break;
			case 2:
				if (dve->element->levo!=NULL) {
					fl=0;
					dve->element->levo=NULL;
					}
				break;
		}
	}

	tek=dve;
	dve=dve->sledeci;
	free(tek);
}

void azuriraj_postF1(skup_trougao_t *pronadjen, int q){
	Cv_t *tekuci;

	tekuci=pronadjen->element;

	switch(q){
		case 0: 
			tekuci->osnova->osnova=NULL;
			tekuci->osnova->stepen_veze++;
			tekuci->osnova=NULL;
			tekuci->stepen_veze++;
			break;
		case 1: 
			tekuci->desno->levo=NULL;
			tekuci->desno->stepen_veze++;
			tekuci->desno=NULL;
			tekuci->stepen_veze++;
			break;
		case 2: 
			tekuci->levo->desno=NULL;
			tekuci->levo->stepen_veze++;
			tekuci->levo=NULL;
			tekuci->stepen_veze++;
			break;
	}
}

skup_trougao_t *potez_trougaona(skup_trougao_t *sve, int igrac){
	int fl=1,m,x,p,q,fl2=1;
	skup_trougao_t *pronadjeni;

	while (fl) {
		
		while (sve!=NULL){
			m=rand()/(double)RAND_MAX*(80); //srediti opsege
			pronadjeni=setanje_trougaona(sve,m);
			if (provera_f1_trougaona(pronadjeni->element)){
				break;	
			}else{
				sve=brisanje_skup_trougao(sve, pronadjeni);
			}
		}
		
		if (sve==NULL) {
			break;
		}

		x=rand()/(double)RAND_MAX*3;

		for (p=0; p<2 && fl2; p++) {
		q=(x+p)%3;
		switch(q) {
			case 0:
				if (pronadjeni->element->osnova!=NULL) {
					if (provera_f1_trougaona(pronadjeni->element->osnova)) {
						fl=0;
						fl2=0;
						break;
					}
				}else break;
			case 1:
				if (pronadjeni->element->desno!=NULL) {
					if (provera_f1_trougaona(pronadjeni->element->desno)) {
						fl=0;
						fl2=0;
						break;
					}
				}else break;
			case 2:
				if (pronadjeni->element->levo!=NULL) {
					if (provera_f1_trougaona(pronadjeni->element->levo)) {
						fl=0;
						fl2=0;
						break;
					}
				}else break;		}
		}

		if (fl) {
			sve=brisanje_skup_trougao(sve,pronadjeni);
		}
	}

	if (sve!=NULL){
		azuriraj_postF1(pronadjeni, q);
		sve=brisanje_skup_trougao(sve,pronadjeni);
	}

	return sve;
}

int faza1_t(Cv_t *matrica, skup_trougao_t *dve, skup_trougao_t *sve, int igrac){

	if (dve!=NULL){
		dve=zatvaranje_t(dve);
		return 1;
	}else{
		sve=potez_trougaona(sve, igrac);
		return 0;
	}
}