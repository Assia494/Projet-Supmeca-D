
Chainon_age *creer_chainon_age(int age){
Chainon_age *nouveau = malloc(sizeof(Chainon_age));
	exit_if_null_pointer(nouveau);
	nouveau->age = age;
	for (int i = 0; i < 3; i++) {
    	 for (int j = 0; j < 5; j++) {
       	 	n->compteurs[i][j] = 0;
   		 }
    }
    n->suivant = NULL;
	nouveau->suivant = NULL;
	return nouveau;
}

void liberer_liste_ages (Chainon_age* tete){
    Chainon_age courant = tete;
	Chainon_age* suivant = NULL;

	while(courant != NULL){
        suivant = courant->suivant;
		free(courant);
		courant = suivant;
	}
}

Chainon_age* inserer_ou_maj_age(Chainon_age *tete, LigneCSV ligne) {
    int age = calculer_age(ligne.year, ligne.birth_year);
	Chainon_age **ptete = &tete;
	Chainon_age *courant = *ptete ;

    /* Donnee incoherente (annee de naissance apres l'accident, etc.) : on ignore */
    if (age < 0) {
        return tete;
    }

    /* Recherche de la position : on avance tant que l'age du chainon est plus petit */
    
    while (*ptete != NULL && (*ptete)->age < age) {
        ptete = &(*ptete)->suivant;
    }

    /* Age absent de la liste : on cree un chainon et on l'insere a cette position */
    if (*ptete == NULL || (*ptete)->age != age) {
        Chainon_age *nouveau = creer_chainon_age(age);
        nouveau->suivant = *ptete;
        *ptete = nouveau;
    }


    /* Mise a jour des compteurs (indices proteges contre les valeurs hors limites) */
        if ((ligne.gender == MASCULIN || ligne.gender == FEMININ) && (ligne.user_type >= CONDUCTEUR && ligne.user_type <= PIETON)) {
       		 courant->compteurs[ligne.gender][ligne.user_type]++ ;
    }
    return tete;
}


Chainon_age* charger_age_data(const char *chemin_csv) {
    FILE *fichier = openFile(chemin_csv);      /* quitte le programme si echec */
    Chainon_age *tete = NULL;
    LigneCSV ligne;
    int resultat = 0;

    while ((resultat = lire_ligne_csv(fichier, &ligne)) != 0) {

        /* Ligne mal formee : on l'ignore et on continue */
        if (resultat == -1) {
            continue;
        }

        /* Ignore les lignes hors intervalle (dont l'en-tete, lu avec year = 0) */
        if (!verif_year(ligne.year, 2005, 2024)) {
            continue;
        }

        tete = inserer_ou_maj_age(tete, ligne);
    }

    fclose(fichier);
    return tete;
}


