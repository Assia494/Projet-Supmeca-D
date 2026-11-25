

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

int hauteur_avl(){
    exit_if_null_pointer
}
