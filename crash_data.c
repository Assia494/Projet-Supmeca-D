
int* cree_tab_year(int size) { 

	int tab_stat[size] = {0} ; 

    for (int i = 0; i < size; i++) {
        tab_stat[i] = 0;
    }

    return tab_stat;
}

	return vic;
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
	Vehicule *nouveau_vehicule = creer_vehicule(ligne.vehicule_id, ligne.purpose);
	while(courant !=NULL){
		if(courant->vehicule_id==0){
			
			courant->victime = ajouter_victime(courant->victime, ligne);
			return courant;
			
		}
		courant=courant->suivant;
	}
	nouveau_vehicule->victime = ajouter_victime(nouveau_vehicule->victime, ligne);
	nouveau-vehicule->suivant = *tete;
	
	*tete =nouveau_vehicule;
	return nouveau_vehicule;
}


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



