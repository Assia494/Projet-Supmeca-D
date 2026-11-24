
void exit_if_null_pointer(void* pointer) {                              // utile pour apres un malloc 
	if(pointer == NULL) {
		printf("pointer nul\n");
		exit(1);
	}
}

int verif_year(int nb,int y1,int y2) {                                   
	return (y1<=nb)&&(nb<=y2);                                         // 1 si verifié et 0 sinon
}

int calcul_age(Victime *v, year_collision_id *annee_col){
    exit_if_null_pointer(v);
    exit_if_null_pointer(annee_col);
    return annee_col - v->birth_year;
}

PURPOSE convertPurpose(int valeur) {
    if (valeur >= AUTRES) {
        return AUTRES; // Toute valeur >= 6 est ramenée à 6
    }
    if(valeur<=NON_RENSEIGNE){
    return NON_RENSEIGNE;
    }
    return (Purpose)valeur;
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

void affiche_stat(int stat_annee_tab[], int annee){   //FONCTION A VERIFIER tant que on l indice ne correspond pas a l indice de l annee pris en parametre on continue de parcourri de tableau et quand ca retrouve on s arrete 
	if(verif_year(annee, 2005, 2024))
    int i =0;
	while{indice_annee(annee)!= i){
    stat_annee_tab[i++]
    
	}

Victime* creer_victime(LigneCSV ligne){
    Victime* v = malloc(sizeof(Victime));
	exit_if_null_pointer(v);

	v->user_type = ligne.user_type;
	v->severity = ligne.severity;
	v->gender = ligne.gender;
	v->birth_year = ligne.birth_year;
	v->location = ligne.location;
	v->suivant = NULL;

	return v;
}

Vehicule* creer_vehicule(int vehicule_id, int purpose){
    Vehicule* vehicule = malloc(sizeof(Vehicule));
	exit_if_null_pointer(vehicule);

	vehicule->vehicule_id = vehicule_id;
	vehicule->purpose = purpose;
    vehicule->suivant = NULL;
	vehicule->victime = NULL;

	return vehicule;
}

Victime* ajouter_victime(Victime* tete, LigneCSV ligne){
    Victime* vic = creer_victime(ligne);

	vic->suivant = tete;

	return vic;
}

Vehicule* trouver_ajouter_vehicule(Vehicule **tete, LigneCSV ligne){
	Vehicule *courant = *tete;
	Vehicule *nouveau_vehicule=creer_vehicule(ligne.vehicule_id, ligne.purpose);
	while(courant !=NULL){
		if(courant->vehicule_id==0){
			courant->victime=ajouter_victime(courant->victime, ligne);
			return courant;
		}
		courant=courant->suivant;
	}
	nouveau_vehicule->victime=ajouter_victime(nouveau_vehicule->victime, ligne);
	nouveau-vehicule->suivant =*tete;
	*tete =nouveau_vehicule;
	return nouveau_vehicule;
}

