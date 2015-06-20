#ifndef NESTO
#define NESTO
#include "tips.h"

void kreiranje_polja_pravougaona(Cvor matrica[100][100], int m, int n);
skup_pravougaonik_t *inic_skup(Cvor matrica[100][100], int m, int n);
skup_pravougaonik_t *setanje(skup_pravougaonik_t *prvi_s, int x);
skup_pravougaonik_t *brisanje(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *element);
int faza_1(zajedno *a);
void zatvaranje(Cvor *matrica);
skup_pravougaonik_t *azuriranje_skupa_prvi(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *node);
skup_pravougaonik_t *azuriranje_sanse(Cvor matrica[100][100], int m, int n);
void obrisi_listu(skup_pravougaonik_t *prvi);
void odigraj(Cvor matrica[100][100], koordinate a);
void azuriranje_post_f1(skup_pravougaonik_t *node, int q);

#endif