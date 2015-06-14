#include <stdio.h> 
#include <stdlib.h> 

typedef struct cv{

	struct cv *gore, *dole, *levo, *desno;
	int weight_up, weight_down, weight_right, weight_left;
	int posecen, seen;
	int stepen_veze;
	int vlasnik;
	int tip;

}Cvor;
Cvor * pronadjipocetak(Cvor * tekuci)
{
	//Dok postoji neki put kojim se nije islo tekuci ce da ide tim putem, i stavlja polje seen na 1. kada nema vise cvorova za koje vazi da je tip 2, seen 0
	// i stepen veze manji od 2, pocetak je nadjen.
	int uslov;
	tekuci->posecen = 1;
	if (tekuci->stepen_veze > 2)
		return NULL;
	while (tekuci->stepen_veze <= 2 && tekuci->tip == 2)
	{
		uslov = 0;
		while (tekuci->dole != NULL && tekuci->dole->tip == 2 && tekuci->dole->seen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->dole;
			tekuci->seen = 1;
			uslov = 1;
		}
		while (tekuci->desno != NULL && tekuci->desno->tip == 2 && tekuci->desno->seen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->desno;
			tekuci->seen = 1;
			uslov = 1;
		}
		while (tekuci->levo != NULL && tekuci->levo->tip == 2 && tekuci->levo->seen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->levo;
			tekuci->seen = 1;
			uslov = 1;
		}
		while (tekuci->gore != NULL && tekuci->gore->tip == 2 && tekuci->gore->seen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->gore;
			tekuci->seen = 1;
			uslov = 1;
		}
		if (uslov == 0)
			return tekuci;
	}
}
void smesti_niz(Cvor* tekuci, int brojac, Cvor *pocetak[], Cvor *kraj[], int duzina[], Cvor *igrajp[], Cvor *igrajk[], int duz[])
{
	//Procedura slicna kao u pronadji pocetak. Popunjava se samo polje posecen.
	// Ako pocetak ili kraj imaju stepen veze 1, onda se taj niz smesta u posebne vektore za igranje.
	Cvor *prvi;
	int uslov, vrednost = 1;
	prvi = (Cvor*)malloc(sizeof(Cvor));
	prvi = tekuci;
	tekuci->posecen = 1;

	if (tekuci->stepen_veze != 2)
	while (tekuci->stepen_veze <= 2 && tekuci->tip == 2)
	{
		uslov = 0;
		vrednost = 1;
		while (tekuci->dole != NULL && tekuci->dole->tip == 2 && tekuci->dole->posecen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->dole;
			tekuci->posecen = 1;
			uslov = 1;
			vrednost++;
		}
		while (tekuci->desno != NULL && tekuci->desno->tip == 2 && tekuci->desno->posecen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->desno;
			tekuci->posecen = 1;
			uslov = 1;
			vrednost++;
		}
		while (tekuci->levo != NULL && tekuci->levo->tip == 2 && tekuci->levo->posecen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->levo;
			tekuci->posecen = 1;
			uslov = 1;
			vrednost++;
		}
		while (tekuci->gore != NULL && tekuci->gore->tip == 2 && tekuci->gore->posecen == 0 && tekuci->stepen_veze <= 2)
		{
			tekuci = tekuci->gore;
			tekuci->posecen = 1;
			uslov = 1;
			vrednost++;
		}
		if (uslov == 0)
			break;
	}
	if (prvi->stepen_veze == 2 && tekuci->stepen_veze == 2)
	{
		pocetak[brojac] = prvi;
		kraj[brojac] = tekuci;
		duzina[brojac] = vrednost;
	}
	else
	{
		while (1)
		{
			if (igrajp[0] == NULL)
			{
				igrajp[0] = prvi;
				igrajk[0] = tekuci;
				duz[0] = vrednost;
				break;
			}
			if (igrajk[1] == NULL)
			{
				igrajp[1] = prvi;
				igrajk[1] = tekuci;
				duz[1] = vrednost;
				break;
			}
			if (igrajk[2] == NULL)
			{
				igrajp[2] = prvi;
				igrajk[2] = tekuci;
				duz[2] = vrednost;
				break;
			}

			break;
		}
	}
}
int nizovi(Cvor *lista[], Cvor *pocetak[], Cvor *kraj[], int duzina[], int brkolona, int brvrsta,Cvor *igrajp[], Cvor *igrajk[], int duz[] )
{
	Cvor * tekuci;
	int i, j, vrednost, brojac = 0;;
	for (i = 1; i <= brkolona; i++)
	{
		for (j = 1; j <= brvrsta; j++)
		{
			tekuci = lista[7 * i + 1 + j];//POPRAVITI U ZAVISNOSTI OD VELICINE POLJA!!!!!!!!!
			if (tekuci->stepen_veze <= 2 && tekuci->posecen == 0 && tekuci->tip==2)
			{
				tekuci = pronadjipocetak(tekuci);
				smesti_niz(tekuci, brojac, pocetak, kraj, duzina,igrajp,igrajk,duz);
				brojac++;
			}
		}
	}
	return brojac;
}
void faza_2(Cvor *matrica, int n, int m)
{
	Cvor *lista[110];
	int brkolona, brvrsta, i, j;
	int duzina[64], vrednost, duz[3];
	Cvor *pocetak[64], *kraj[64], *tekuci, *igrajp[3],*igrajk[3];
	brkolona = m;
	brvrsta = n;

	for (i = 0; i<m*n + 1; i++)
	{
		lista[i] = (Cvor*)malloc(sizeof(Cvor));
		lista[i]->posecen = 0;
		lista[i]->stepen_veze = matrica[i].stepen_veze;
		lista[i]->vlasnik = matrica[i].vlasnik;
		lista[i]->tip = matrica[i].tip;
	}
	for (i = 0; i<m*n + 1; i++)
	{
		lista[i]->levo = matrica[i].levo;
		lista[i]->desno = matrica[i].desno;
		lista[i]->gore = matrica[i].gore;
		lista[i]->dole = matrica[i].dole;
	}
	for (i = 0; i<(brkolona + 2)*(brvrsta + 2) + 1; i++)
	{
		lista[i]->posecen = 0;
		lista[i]->seen = 0;
	}
	for (i = 0; i<63; i++)
	{
		pocetak[i] = (Cvor*)malloc(sizeof(Cvor));
		kraj[i] = (Cvor*)malloc(sizeof(Cvor));;
		pocetak[i] = NULL;
		kraj[i] = NULL;
		duzina[i] = 0;
	}
	for (i = 0; i < 3; i++)
	{
		igrajp[i] = (Cvor*)malloc(sizeof(Cvor));
		igrajk[i] = (Cvor*)malloc(sizeof(Cvor));
		igrajp[i] = NULL;
		igrajk[i] = NULL;
		duz[i] = 0;
	}

	nizovi(lista, pocetak, kraj, duzina, brkolona, brvrsta, igrajp,igrajk,duz);
/// funkcija za pronalazenje cvorova sa stepenom veze 3 i postavljanje veza.
/// faza za igranje...
}