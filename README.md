# crtice-i-kutijice



-implementacija svih potrebnih struktura je zavrsena

-faza 1 (sto pretstavlja ceo easy nivo kao i pocetak medium a i hard a) je zavrsena 90%

-logika igre

koordinate nadji_elemente(Cvor *node, int q){
	extern Cvor matrica[100][100];
	extern int m, n;
	int i = 1, j = 1, fl = 1;
	koordinate vrati;


	for (i = 0; i < n && fl; i++){
		for (j = 0; j < m; j++)
			if (node == &matrica[i][j]) {
				vrati.x1 = i;
				vrati.y1 = j;
				fl = 0;
				break;
			}
	}

	switch (q){
		case 0:	
			vrati.x2 = i - 1;
			vrati.y2 = j;
			break;
		case 1: 
			vrati.x2 = i;
			vrati.y2 = j + 1;
			break;
		case 2: 
			vrati.x2 = i + 1;
			vrati.y2 = j;
			break;
		case 1:
			vrati.x2 = i;
			vrati.y2 = j - 1;
			break;
	
	}


	return vrati;

}
