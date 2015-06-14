#include "tipovi.h"
#include "zaglavlje_t.h"
#include "zaglavlje_p.h"
//UKLJUCITI STA TREBA

int igrac;

void oboj(skup_pravougaonik_t *node){

	node->element->vlasnik=igrac;

}

int igra_pravougaona(Cvor matrica[100][100], int m, int n, int tezina){
	skup_pravougaonik_t *prvi=NULL, *sansa=NULL;
	int fl;
	
	igrac=0;

	prvi=inic_skup(matrica,m,n);

	while(prvi!=NULL){
		while(faza_1(prvi,sansa,igrac));
		igrac=!igrac;
		if (prvi==NULL) break;
		/*	do{
				traziti od igraca da igra; -MINA		
				*/
			sansa=azuriranje_sanse(sansa,matrica,m,n);		
			/*
			}while(igrac zatvara polja); ALI OVO SE NIKAD NECE DESITI U PRVOJ FAZI
		*/
	}
	//faza 2
	return 0;
}



int main(){
	int izbor,m,n,h,tezina;
	Cvor matrica_pravougaonik[100][100];
	Cv_t niz_trougao[100];

	
	switch(izbor){
		case 1:
			//dobijas m i n
			kreiranje_polja_pravougaona(matrica_pravougaonik, m, n);
			//traziti tezinu
			//igra_pravougaona
			break;
		
		case 2:
			//dobijas h
			//inicijalizacija struktura
			//traziti tezinu
			//igra_trougaona
			break;
	}

	return 0;
}