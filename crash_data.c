

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

int hauteur_AVL(Noeud_AVL* noeud){
    exit_if_null_pointer(noeud);

	return noeud->hauteur;
}

int facteur_equilibre(Noeud_AVL* noeud){
     exit_if_null_pointer(noeud);
	
    return hauteur_avl(noeud->fg) - hauteur_avl(noeud->fg);
}

Noeud_AVL* rotation_droite(Noeud_AVL* noeud){
    exit_if_null_pointer(noeud);
	
    Noeud_AVL* pivot = NULL;
	int eq_noeud = 0;
	int eq_p = 0;

	pivot = noeud->fg;
	noeud->fg = pivot->fd;
	pivot->fd = noeud;

	eq_noeud = noeud->equilibre;
	eq_p = pivot->equilibre;

	noeud->equilibre = eq_noeud - min_val_2(eq_p, 0) + 1;
	pivot->equilibre = max_val_3(eq_noeud + 2, eq_noeud + eq_p + 2, eq_p + 1);
	noeud = pivot;
	
    return noeud;
}

Noeud_AVL* rotation_gauche(Noeud_AVL* noeud){
	exit_if_null_pointer(noeud);

	Noeud_AVL* pivot = NULL;
	int eq_noeud = 0;
	int eq_p = 0;

	pivot = noeud->fd;
	noeud->fd = pivot->fg;
	pivot->fg = noeud;

	eq_noeud = noeud->equilibre;
	eq_p = pivot->equilibre;

	noeud->equilibre = eq_noeud - max_val_2(eq_p, 0) - 1;
	pivot->equilibre = min_val_3(eq_noeud - 2, eq_noeud + eq_p - 2, eq_p - 1);
	noeud = pivot;

	return noeud;
}

Noeud_AVL* creer_noeud_AVL(unsign long long cle, LigneCSV ligne){
    Noeud_AVL* nouveau_noeud = malloc(sizeof(Noeud_AVL));

    exit_if_null_pointer(nouveau_noeud);

    nouveau_noeud->cle_accidnt = cle;
    nouveau_noeud->vehicule = ligne.vehicule_id;
    nouveau_noeud->hauteur = 1;
    nouveau_noeud->fg = NULL;
    nouveau_noeud->fd = NULL;

    return ;
}

Noeud_AVL* equilibrer(Noeud_AVL* noeud, unsign long long  cle){
    int balance = facteur_equilibre(noeud);

	if(balance > 1 && cle < noeud->gauche->cle){
        return rotation_droite(noeud);
	}

	if(balance < -1 && cle < noeud->droit->cle){
        return rotation_gauche(noeud);
	}

	if(balance > 1 && cle > noeud->gauche->cle){
		noeud->fg = rotation_gauche(noeud->fg);
        return rotation_droite(noeud);
	}

	
	if(balance < -1 && cle < noeud->droit->cle){
		noeud->fd = rotation_droit(noeud->fd);
        return rotation_gauche(noeud);
	}

	return noeud;
}

Noeud_AVL* insertion_AVL(Noeud_AVL* noeud, unsign long long  cle, LigneCSV ligne, int* hauteur){
    exit_if_null_pointer(hauteur);
	
    if(noeud == NULL){
		Noeud_AVL* nouveau = creer_noeud_AVL(cle);
		nouveau->vehicule = trouver_ajouter_vehicule(&(nouveau->vehicule), ligne);
		return nouveau;
	}

	else if (cle < noeud->cle_accident){
        noeud->fg = insertion_AVL(noeud->fg, cle, ligne, hauteur);
	}

	else if (cle > noeud->cle_accident){
        noeud->fd = insertion_AVL(noeud->fd, cle, ligne, hauteur);
	}

	else{
		noeud->vehicule = trouver_ajouter_vehicule(&(nouveau->vehicule), ligne);
		return noeud;
	}

	noeud_hauteur = 1 + max_val_2(hauteur_AVL(noeud->fg), hauteur_AVL(noeud->fd));

	return  equilibrer(noeud, cle);
}
