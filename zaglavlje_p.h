#include "tipovi.h"

void kreiranje_polja_pravougaona(Cvor matrica[100][100], int m, int n);
skup_pravougaonik_t *inic_skup(Cvor matrica[100][100], int m, int n);
skup_pravougaonik_t *setanje(skup_pravougaonik_t *prvi_s, int x);
skup_pravougaonik_t *brisanje(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *element);
int faza_1(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *prvi_trojka, int igrac);
void zatvaranje(Cvor *matrica);
skup_pravougaonik_t *brisanje(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *element);
skup_pravougaonik_t *setanje(skup_pravougaonik_t *prvi_s, int x);
skup_pravougaonik_t *azuriranje_skupa_prvi(skup_pravougaonik_t *prvi_s, skup_pravougaonik_t *node);
skup_pravougaonik_t *azuriranje_sanse(skup_pravougaonik_t *sansa, Cvor matrica[100][100], int m, int n);