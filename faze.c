#include "nekiHeader.h"
#include <stdlib.h>
#include <time.h>

/*proverava da li moze da se odigra na odredjenom cvoru u matrici*/
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

void oboj(Cvor *matrica, int n, int i, int j, int igrac){
		
	matrica[i*n+j].vlasnik=igrac;
	//

}

//srediti funkciju
void azuriranje_post_f1(Cvor *matrica, int n, int i, int j, int q, int igrac){
	int x,y,a,b;
	Cvor elem;

	switch(q){
		case 0:
			matrica[(i-1)*n+j].dole=NULL;
			matrica[(i-1)*n+j].stepen_veze--;
			
			if (matrica[(i-1)*n+j].tip!=0){
			
				if (matrica[(i-1)*n+j].stepen_veze==0){
					oboj(matrica,n,i-1,j,igrac);	
				}
			}

			matrica[i*n+j].gore=NULL;
			matrica[i*n+j].stepen_veze--;
			if (matrica[i*n+j].stepen_veze==0){
				oboj(matrica,n,i,j,igrac);	
			}
		case 1:
			matrica[i*n+j+1].levo=NULL;
			matrica[i*n+j+1].stepen_veze--;
			
			if (matrica[i*n+j+1].tip!=0){
			
				if (matrica[i*n+j+1].stepen_veze==0){
					oboj(matrica,n,i,j+1,igrac);	
				}
			}

			matrica[i*n+j].desno=NULL;
			matrica[i*n+j].stepen_veze--;
			if (matrica[i*n+j].stepen_veze==0){
				oboj(matrica,n,i,j,igrac);	
			}
		case 2:
			matrica[(i+1)*n+j].gore=NULL;
			matrica[(i+1)*n+j].stepen_veze--;
			
			if (matrica[(i+1)*n+j].tip!=0){
			
				if (matrica[(i+1)*n+j].stepen_veze==0){
					oboj(matrica,n,i+1,j,igrac);	
				}
			}
		case 3:
			matrica[i*n+j-1].desno=NULL;
			matrica[i*n+j-1].stepen_veze--;
			
			if (matrica[i*n+j-1].tip!=0){
			
				if (matrica[i*n+j-1].stepen_veze==0){
					oboj(matrica,n,i,j-1,igrac);	
				}
			}

			matrica[i*n+j].levo=NULL;
			matrica[i*n+j].stepen_veze--;
			if (matrica[i*n+j].stepen_veze==0){
				oboj(matrica,n,i,j,igrac);	
			}
			matrica[i*n+j].dole=NULL;
			matrica[i*n+j].stepen_veze--;
			if (matrica[i*n+j].stepen_veze==0){
				oboj(matrica,n,i,j,igrac);	
			}

	}
}

skup_t *zatvaranje_f1(skup_t *djus){
	skup_t *tek;
	int p, fl=1,i;

	for (p=0; p<3 && fl; p++) {
		switch(p) {
			case 0:
				if (djus->element->gore!=NULL) {
					fl=0;
					djus->element->gore=NULL;
					}
				break;
			case 1:
				if (djus->element->desno!=NULL) {
					fl=0;
					djus->element->desno=NULL;
					}
				break;
			case 2:
				if (djus->element->dole!=NULL) {
					fl=0;					
					djus->element->dole=NULL;
					}
				break;
			case 3:
				if (djus->element->levo!=NULL) {
					fl=0;
					djus->element->levo=NULL;
					}
				break;
		}
	}
	tek=djus;
	djus=djus->sledeci;
	free(tek);
}
skup_t *potez_f1(int igrac, skup_t *prvi_s){
	int i, j, fl=1, fl2=1,x,p,counter=0,u,q;
	Cvor *elem;
	skup_t *pronadjen;
	
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
		azuriranje_post_f1() ;//srediti ovu funkciju SREDIII
		prvi_s=azuriranje_skupova(prvi_s, pronadjen);
	}
	return prvi_s;
}

//terminacija f1 kada je prvi_s == NULL

int faza_1(skup_t *prvi_s, skup_t *prvi_trojka, int igrac){
	

	if (prvi_trojka!=NULL){
		prvi_trojka=zatvaranje_f1(prvi_trojka);
		return 1;
	}else{
		potez_f1(igrac, prvi_s);//uopste nije potrebna matrica;
		return 0;
	}
}



