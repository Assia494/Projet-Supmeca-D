
void exit_if_null_pointer(void* pointer) {                              // utile pour apres un malloc 
	if(pointer == NULL) {
		printf("pointer nul\n");
		exit(1);
	}
}

int verif_year(int nb,int y1,int y2) {                                   
	return (y1<=nb)&&(nb<=y2);                                         // 1 si verifié et 0 sinon
}


int* cree_tab_year(int size) { 

	int tab_stat[size] = {0} ; 

    for (int i = 0; i < size; i++) {
        tab_stat[i] = 0;
    }

    return tab_stat;
}

int indiceAnnee (int year){                    //transforme une annee en position ds tab   i=0 -> 2005, ...
	return year - 2005; 
}

void compter_accidents (pAccident a, int tab_stat[], int * acc){
	exit_if_null_pointer(a);

	int indice = indiceAnnee(a->cle.year);

    if (verif_year(a->cle.year, 2005, 2024)) {
        tab_stat[indice]++;
    }

    compter_accidents(a->fg, tab_stat);
    compter_accidents(a->fd, tab_stat);
}

void compter_gravite(Victime* v, Statistiques* stats) {

    while (v != NULL) {

        switch (v->severity) {

            case 1:
                stats->indemnes++;
                break;

            case 2:
                stats->morts++;
                break;

            case 3:
                stats->blesses_graves++;
                break;

            case 4:
                stats->blesses_legers++;
                break;
        }

        v = v->suivant;
    }
}
