#include "zaglavlje_t.h"


/*Inicijalizacija trougaone matrice*/
Cv_t *inic_t(int h){
	Cv_t matrica[80];	
	int i,j,k,prosli_red=3;
	
	k=0;
	for (i=1; i<=h; i++) {
		for (j=0; j<prosli_red; j++){
			if (j==0) {
				matrica[k].tip=0;
				matrica[k].levo=NULL;
				matrica[k].osnova=NULL;
				matrica[k].desno=&matrica[k+1];
				matrica[k].stepen_veze=1;
				matrica[k].vlasnik=0;
				k++;
				continue;
			}
			if (j==prosli_red-1) {
				matrica[k].tip=0;
				matrica[k].desno=NULL;
				matrica[k].osnova=NULL;
				matrica[k].levo=&matrica[k-1];
				matrica[k].stepen_veze=1;
				matrica[k].vlasnik=0;
				k++;
				continue;
			}
			if (j%2){
				matrica[k].tip=1;
				matrica[k].levo=&matrica[k-1];
				matrica[k].desno=&matrica[k+1];
				matrica[k].osnova=&matrica[k+prosli_red+1];
				matrica[k].stepen_veze=3;
				matrica[k].vlasnik=0;
				k++;
			}else{
				matrica[k].tip=1;
				matrica[k].levo=&matrica[k-1];
				matrica[k].desno=&matrica[k+1];
				matrica[k].osnova=&matrica[k-prosli_red-1];
				matrica[k].stepen_veze=3;
				matrica[k].vlasnik=0;
				k++;
			}
		}
		prosli_red+=2;
	}
	
	matrica[k].tip=-1;
	for (i=0; i<prosli_red; i++){
		if (i==i || i==prosli_red-1) {
			k++;
			continue;
		}
		if (i%2==0){
			matrica[k].tip=0;
			matrica[k].levo=NULL;
			matrica[k].desno=NULL;
			matrica[k].osnova=&matrica[k-prosli_red+1];
			matrica[k].stepen_veze=1;
			matrica[k].vlasnik=0;
			k++;
		}else{
			k++;
		}
	}

	return matrica;
}

/*inicijalizuje skup koji pretstavlja u pocetku sve cvorove na kojima moze da se igra*/
skup_trougao_t *inic_skup_trougao(Cv_t *matrica){
	skup_trougao_t *prvi, *novi, *pom, *prethodni;
	int i;

	prvi=NULL;
	for (i=0; matrica[i].tip!=-1; i++){
		if (matrica[i].tip==0) continue;
		
		pom=(skup_trougao_t*)malloc(sizeof(skup_trougao_t));
		if (pom==NULL) exit(2);
		
		novi=pom;
		novi->element=&matrica[i];
		novi->sledeci=NULL;
		if (prvi==NULL){
			prvi=novi;
		}else{
			prethodni->sledeci=novi;
		}
		prethodni=novi;
	}

	return prvi;
}

/**/
skup_trougao_t *brisanje_skup_trougao(skup_trougao_t *prvi, skup_trougao_t *element){
	skup_trougao_t *prethodni;

	if (prvi==element){
		prvi=prvi->sledeci;
		free(element);
	}else{
		while (prethodni->sledeci!=element) {
			prethodni=prethodni->sledeci;
		}
		prethodni->sledeci=element->sledeci;
		free(element);
	}

	return prvi;
}

/*Uz pomoc ovog ide RANDOM*/
skup_trougao_t *setanje_trougaona(skup_trougao_t *prvi, int x){
	skup_trougao_t *tekuci=prvi;

	while (x) {
		tekuci=tekuci->sledeci;
		if (tekuci==NULL) {
			tekuci=prvi;
		}
		--x;
	}

	return tekuci;
}

int provera_f1_trougaona(Cv_t *elem){
	

	if (elem->vlasnik!=0) return 0;

	if (elem->tip==1){
		if (elem->stepen_veze<3) return 0;
		else return 1;
	}else{
		if (elem->stepen_veze==1) return 1;
		else return 0;
	}
}

skup_trougao_t *azuriranje_sk_t(skup_trougao_t *prvi, skup_trougao_t *node){

	if (node->element->stepen_veze == 2){
		prvi=brisanje_skup_trougao(prvi,node);
	}

	return prvi;
}





