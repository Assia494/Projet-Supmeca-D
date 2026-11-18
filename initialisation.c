
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

	for(int i =; i< SIZE, i++){
	(*acc)++; // Incrémente le nombre d 'accidents
	
	compter_accidents(tab_stat[i], a->fg, acc);
	
	compter_accidents(tab_stat[i], a->fd, acc);

	}
}

void compter_severity (pAccident a, int * acc){
	exit_if_null_pointer(a);
	(*acc)++;
	compter_severity(a->fg->tete_vehicule->victime->severity, acc);
	compter_severity(a->fd->tete_vehicule->victime->severity, acc);
}
