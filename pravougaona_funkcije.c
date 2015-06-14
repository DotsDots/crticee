#include "tipovi.h"
#include <time.h>


int provera_f1(Cvor elem){
	

	if (elem.vlasnik!=0) return 0;

	if (elem.tip==1){
		if (elem.stepen_veze<3) return 0;
		else return 1;
	}else{
		if (elem.stepen_veze==1) return 1;
		else return 0;
	}
}
void azuriranje_post_f1(skup_pravougaonik_t *node, int q){
	
		switch(q){
		case 0:
			node->element->gore->dole=NULL;
			node->element->gore->stepen_veze--;
			node->element->gore=NULL;
			node->element->stepen_veze--;
		case 1:
			node->element->desno->levo=NULL;
			node->element->desno->stepen_veze--;
			node->element->desno=NULL;
			node->element->stepen_veze--;
		case 2:
			node->element->dole->gore=NULL;
			node->element->dole->stepen_veze--;
			node->element->dole=NULL;
			node->element->stepen_veze--;
		case 3:
			node->element->desno->levo=NULL;
			node->element->desno->stepen_veze--;
			node->element->desno=NULL;
			node->element->stepen_veze--;
	}
	
}
skup_pravougaonik_t *zatvaranje_f1(skup_pravougaonik_t *node){
	skup_pravougaonik_t *tek;
	int p, fl=1,i;

	for (p=0; p<3 && fl; p++) {
		switch(p) {
			case 0:
				if (node->element->gore!=NULL) {
					fl=0;
					node->element->gore=NULL;
					}
				break;
			case 1:
				if (node->element->desno!=NULL) {
					fl=0;
					node->element->desno=NULL;
					}
				break;
			case 2:
				if (node->element->dole!=NULL) {
					fl=0;					
					node->element->dole=NULL;
					}
				break;
			case 3:
				if (node->element->levo!=NULL) {
					fl=0;
					node->element->levo=NULL;
					}
				break;
		}
	}
	tek=node;
	node=node->sledeci;
	//oboj(tek);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	free(tek);
}
skup_pravougaonik_t *potez_f1(int igrac, skup_pravougaonik_t *prvi_s){
	int i, j, fl=1, fl2=1,x,p,counter=0,u,q;
	Cvor *elem;
	skup_pravougaonik_t *pronadjen;
	
	//
	
	srand(time(NULL));

	while (fl) {
		
		while (prvi_s!=NULL){
			u=rand()/(double)RAND_MAX*(80);
			pronadjen=setanje(prvi_s,u);
			if (provera_f1(*(pronadjen->element))){
				break;	
			}else{
				prvi_s=brisanje(prvi_s,pronadjen);
			}
		}
		
		if (prvi_s==NULL) {
			break;
		}

		x=rand()/(double)RAND_MAX*3;

		for (p=0; p<3 && fl2; p++) {
		q=(x+p)%4;
		switch(q) {
			case 0:
				if (pronadjen->element->gore!=NULL) {
					if (provera_f1(*(pronadjen->element)->gore)) {
						fl=0;
						fl2=0;
						break;
					}
				}else break;
			case 1:
				if (pronadjen->element->desno!=NULL) {
					if (provera_f1(*(pronadjen->element)->desno)){
						fl=0;					
						fl2=0;
						break;
					}
				}else break;
			case 2:
				if (pronadjen->element->dole!=NULL) {
					if (provera_f1(*(pronadjen->element)->dole)) {
						fl=0;					
						fl2=0;
						break;
					}
				}else break;
			case 3:
				if (pronadjen->element->levo!=NULL) {
					if (provera_f1(*(pronadjen->element)->levo)){
						fl=0;
						fl2=0;
						break;
					}
				}else break;
		}
		}

		if (fl) {
			prvi_s=brisanje(prvi_s,pronadjen);
		}
	}

	if (prvi_s!=NULL){
		azuriranje_post_f1(pronadjen,q) ;//srediti ovu funkciju SREDIII
		prvi_s=azuriranje_skupa_prvi(prvi_s, pronadjen);
	}
	return prvi_s;
}
int faza_1(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *prvi_trojka, int igrac){
	

	if (prvi_trojka!=NULL){
		prvi_trojka=zatvaranje_f1(prvi_trojka);
		return 1;
	}else{
		potez_f1(igrac, prvi_s);
		return 0;
	}
}
void kreiranje_polja_pravougaona(Cvor matrica[100][100], int m, int n){
	int i, j;

	for (i=0; i<m+2; i++) {
		for (j=0; j<n+2; j++) {
			if (i==0 && j==0) continue;
			if (i==0 && j==n+1) continue;
			if (i==m+1 && j==0) continue;
			if (i==m+1 && j==n+1) continue;

			if ((i==0) || (j==0) || (j==n+1) || (i==n+1)){
				matrica[i][j].vlasnik=0;
				matrica[i][j].stepen_veze=1;
				matrica[i][j].tip=0;
				if (i==0) {
					matrica[i][j].dole=&matrica[i+1][j];
					matrica[i][j].levo=matrica[i][j].gore=matrica[i][j].desno=NULL;
				}
				if (j==0) {
					matrica[i][j].desno=&matrica[i][j+1];
					matrica[i][j].levo=matrica[i][j].gore=matrica[i][j].dole=NULL;
				}
				if (j==n+1) {
					matrica[i][j].levo=&matrica[i][j-1];
					matrica[i][j].desno=matrica[i][j].gore=matrica[i][j].dole=NULL;
				}
				if (i==m+1) {
					matrica[i][j].gore=&matrica[i-1][j];
					matrica[i][j].levo=matrica[i][j].gore=matrica[i][j].desno=NULL;
				}
			}else{
				matrica[i][j].vlasnik=0;
				matrica[i][j].stepen_veze=4;
				matrica[i][j].tip=1;
			
				matrica[i][j].gore=&matrica[i-1][j];
				matrica[i][j].dole=&matrica[i+1][j];
				matrica[i][j].desno=&matrica[i][j+1];
				matrica[i][j].levo=&matrica[i][j-1];
			}
		}
	}
}
skup_pravougaonik_t *inic_skup(Cvor matrica[100][100], int m, int n){
	skup_pravougaonik_t *pomocni, *prethodni, *novi, *prvi;
	int i,j;

	prvi=NULL;

	for (i=0; i<m; i++)
		for (j=0; j<n; j++){
			if (matrica[i][j].tip!= 1) continue;
			else{
				pomocni=(skup_pravougaonik_t*)malloc(sizeof(skup_pravougaonik_t));
				if (pomocni==NULL) exit(2);
				novi=pomocni;
				novi->element=&matrica[i][j];
				novi->sledeci=NULL;
				if (prvi==NULL){
					prvi=novi;
					prethodni=novi;
				}else{
					prethodni->sledeci=novi;
					prethodni=novi;
				}
			}		
	}
	return prvi;
}
skup_pravougaonik_t *setanje(skup_pravougaonik_t *prvi_s, int x){
	skup_pravougaonik_t *tekuci=prvi_s;

	while (x) {
		tekuci=tekuci->sledeci;
		if (tekuci==NULL) {
			tekuci=prvi_s;
		}
		--x;
	}

	return tekuci;
}
skup_pravougaonik_t *brisanje(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *element){
	skup_pravougaonik_t *prethodni=prvi_s;
	
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
skup_pravougaonik_t *azuriranje_skupa_prvi(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *node){

	if (node->element->stepen_veze == 2){
		prvi_s=brisanje(prvi_s,node);
	}

	return prvi_s;
}
skup_pravougaonik_t *azuriranje_sanse(skup_pravougaonik_t *sansa, Cvor matrica[100][100], int m, int n){
	skup_pravougaonik_t *novi, *prethodni, *pomocni;
	int i, j;

	if (sansa!=NULL) prethodni=sansa;

	for (i=0; i<m; i++)
		for (j=0; j<n; j++){
			if (matrica[i][j].tip!= 1) continue;
			else{
				pomocni=(skup_pravougaonik_t*)malloc(sizeof(skup_pravougaonik_t));
				if (pomocni==NULL) exit(2);
				novi=pomocni;
				novi->element=&matrica[i][j];
				novi->sledeci=NULL;
				if (sansa==NULL){
					sansa=novi;
					prethodni=novi;
				}else{
					prethodni->sledeci=novi;
					prethodni=novi;
				}
			}		
	}

	return sansa;
}


