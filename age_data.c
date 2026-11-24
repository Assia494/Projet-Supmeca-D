
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

