#include "prav_header.h"
#include <stdio.h>
#include <stdlib.h>
#include "tips.h"

int igrac;

skup_pravougaonik_t *inic_easy(Cvor matrica[100][100], int m, int n){
	skup_pravougaonik_t *novi, *prethodni, *pomocni, *sansa=NULL;
	int i, j;

	for (i = 0; i<m+2; i++)
	for (j = 0; j<n+2; j++){
		if (matrica[i][j].tip != 1 || matrica[i][j].stepen_veze==0) continue;
		else{
			pomocni = (skup_pravougaonik_t*)malloc(sizeof(skup_pravougaonik_t));
			if (pomocni == NULL) exit(2);
			novi = pomocni;
			novi->element = &matrica[i][j];
			novi->sledeci = NULL;
			if (sansa == NULL){
				sansa = novi;
				prethodni = novi;
			}
			else{
				prethodni->sledeci = novi;
				prethodni = novi;
			}
		}
	}

	return sansa;
}




int igra_pravougaona(Cvor matrica[100][100], int m, int n, int tezina){
	koordinate a;
	zajedno b;
	int fl, i, j,x,p,q;
	skup_pravougaonik_t *pronadjen, *prvi_easy;

	igrac = 0;

	b.prvi = inic_skup(matrica, m, n);
	
	pronadjen=b.prvi;

/*	while (pom){
		printf("%d %d %d	", pom->element->stepen_veze, pom->element->i, pom->element->j);
		pom=pom->sledeci;
	}
*/

	b.sansa=NULL;
	while (b.prvi != NULL){
		while (faza_1(&b));
		igrac = !igrac;
		if (b.prvi == NULL) break;
		//dobijes koordinate od Mine

		//ovo ispod ispisuje stepen veze time testiram za sad
	for (i = 0; i < m + 2; i++) {
		for (j = 0; j < n + 2; j++) {
			if (i == 0 && j == 0) { 
				printf("  ");
				continue; 
			}
			if (i == 0 && j == n + 1) {
				printf("  ");
				continue;
			}
		if (i == m + 1 && j == 0) {
				printf("  ");
				continue;
			}
			if (i == m + 1 && j == n + 1) {
				printf("  ");
				continue;
			}
			printf("%d ", matrica[i][j].stepen_veze);
		
		}
		printf("\n");
	}
		system("cls");
		scanf("%d%d%d%d", &a.x1,&a.y1,&a.x2,&a.y2);
		odigraj(matrica, a);
		obrisi_listu(b.sansa);
		b.sansa = azuriranje_sanse(matrica, m, n);
		obrisi_listu(b.prvi);

		for (i = 0; i < m + 2; i++) {
		for (j = 0; j < n + 2; j++) {
			if (i == 0 && j == 0) { 
				printf("  ");
				continue; 
			}
			if (i == 0 && j == n + 1) {
				printf("  ");
				continue;
			}
		if (i == m + 1 && j == 0) {
				printf("  ");
				continue;
			}
			if (i == m + 1 && j == n + 1) {
				printf("  ");
				continue;
			}
			printf("%d ", matrica[i][j].stepen_veze);
		
		}
		printf("\n");
	}
		b.prvi=inic_skup(matrica,m,n);	
		system("cls");
	}

	switch (tezina){
	case 1: 
		prvi_easy=inic_easy(matrica, m, n);

		while (prvi_easy){
			x=rand();
			pronadjen=setanje(prvi_easy,x);
			fl=1;
			x = rand() / (double)RAND_MAX * 3;
			for (p = 0; p<3 && fl; p++) {
			q = (x + p) % 4;
			switch (q) {
			case 0:
				if (pronadjen->element->gore != NULL) {
						fl = 0;
					break;
				}
				else break;
			case 1:
				if (pronadjen->element->desno != NULL) {
						fl = 0;
						break;
				}
				else break;
			case 2:
				if (pronadjen->element->dole != NULL) {
						fl = 0;
						break;
				}
				else break;
			case 3:
				if (pronadjen->element->levo != NULL) {
						fl = 0;
						break;
				}
				else break;
			}
		}
			scanf("%d%d%d%d", &a.x1,&a.y1,&a.x2,&a.y2);
			odigraj(matrica, a);
			azuriranje_post_f1(pronadjen, q);
			obrisi_listu(prvi_easy);
			prvi_easy=inic_easy(matrica, m ,n);
		}

		break;
	case 2:
		//napisi easy
		break;
	case 3:
		break;
	case 4:
		break;
	}
	return 0;
}


int main(){
	int izbor, m = 2, n = 2, h, tezina=1;
	Cvor matrica_pravougaonik[100][100];
	//Cv_t niz_trougao[100];
	izbor = 1;

	switch (izbor){
	case 1:
		//dobijas m i n
		kreiranje_polja_pravougaona(matrica_pravougaonik, m, n);
		//traziti tezinu
		igra_pravougaona(matrica_pravougaonik, m,n,tezina);
		break;

	case 2:
		//dobijas h
		//inicijalizacija struktura
		//traziti tezinu
		//igra_trougaona
		break;
	case 3:
		break;
	case 4:
		break;
	}

	return 0;
}