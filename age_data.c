
Chainon_age *creer_chainon_age(int age){
Chainon_age *nouveau = malloc(sizeof(Chainon_age));
	exit_if_null_pointer(nouveau);
	nouveau->age = age;
	memset(nouveau->compteurs_genre, 0, sizeof(nouveau->compteurs_genre));
	memset(nouveau->compteur_usager, 0, sizeof(nouveau->compteur_usager));
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
	Chainon_age **p = &tete;
	Chainon_age *courant = *p;

    /* Donnee incoherente (annee de naissance apres l'accident, etc.) : on ignore */
    if (age < 0) {
        return tete;
    }

    /* Recherche de la position : on avance tant que l'age du maillon est plus petit */
    
    while (*p != NULL && (*p)->age < age) {
        p = &(*p)->suivant;
    }

    /* Age absent de la liste : on cree un maillon et on l'insere a cette position */
    if (*p == NULL || (*p)->age != age) {
        Chainon_age *nouveau = creer_noeud_age(age);
        nouveau->suivant = *p;
        *p = nouveau;
    }


    /* Mise a jour des compteurs (indices proteges contre les valeurs hors limites) */
    if (ligne.gender == MASCULIN || ligne.gender == FEMININ) {
        courant->compteurs_genre[ligne.gender]++;
    }

    if (ligne.user_type >= CONDUCTEUR && ligne.user_type <= PIETON) {
        courant->compteur_usager[ligne.user_type]++;
    }

    return tete;
}

