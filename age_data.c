
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


#define LARGEUR_BARRE 30

/* Nombre de victimes d'un age donne pour un genre, en tenant compte du filtre usager */
static int compter_age(Chainon_age *n, int genre, int filtre_usager) {
    int total = 0;

    for (int u = CONDUCTEUR; u <= PIETON; u++) {
        if (filtre_usager == 0 || filtre_usager == u) {
            total += n->compteurs[genre][u];
        }
    }
    return total;
}

static void afficher_barre(int nb, char c) {
    for (int i = 0; i < nb; i++) {
        putchar(c);
    }
}


/* Compte les victimes d'un chainon (= un age) pour un genre donne,
   en ne gardant que le type d'usager demande (0 = tous les usagers). */
static int compter_victimes_age(Chainon_age *chainon, int genre, int filtre_usager) {
    int nb_victimes = 0;

    for (int type_usager = CONDUCTEUR; type_usager <= PIETON; type_usager++) {
        if (filtre_usager == 0 || filtre_usager == type_usager) {
            nb_victimes += chainon->compteurs[genre][type_usager];
        }
    }
    return nb_victimes;
}

/* Affiche 'nb_caracteres' fois le caractere 'caractere' */
static void afficher_caracteres(int nb_caracteres, char caractere) {
    for (int i = 0; i < nb_caracteres; i++) {
        putchar(caractere);
    }
}

void afficher_pyramide_ages(Chainon_age *tete, int filtre_genre, int filtre_usager) {
    int afficher_hommes = (filtre_genre == 0 || filtre_genre == MASCULIN);
    int afficher_femmes = (filtre_genre == 0 || filtre_genre == FEMININ);

    if (tete == NULL) {
        printf("Aucune donnee a afficher.\n");
        return;
    }

    /* ---- 1er passage : total des victimes retenues et plus grand effectif ---- */
    int total_victimes_retenues = 0;
    int effectif_max = 0;               /* sert a calibrer la longueur des barres */

    for (Chainon_age *chainon = tete; chainon != NULL; chainon = chainon->suivant) {
        int nb_hommes = afficher_hommes ? compter_victimes_age(chainon, MASCULIN, filtre_usager) : 0;
        int nb_femmes = afficher_femmes ? compter_victimes_age(chainon, FEMININ,  filtre_usager) : 0;

        total_victimes_retenues += nb_hommes + nb_femmes;

        if (nb_hommes > effectif_max) effectif_max = nb_hommes;
        if (nb_femmes > effectif_max) effectif_max = nb_femmes;
    }

    if (total_victimes_retenues == 0) {
        printf("Aucune victime ne correspond a ces filtres.\n");
        return;
    }

    /* ---- En-tete ---- */
    printf("\n********** PYRAMIDE DES AGES **********\n");
    printf("Genre  : %s\n", filtre_genre == MASCULIN ? "hommes" :
                            filtre_genre == FEMININ  ? "femmes" : "tous");
    printf("Usager : %s\n", filtre_usager == CONDUCTEUR ? "conducteurs" :
                            filtre_usager == PASSAGER   ? "passagers"   :
                            filtre_usager == PIETON     ? "pietons"     : "tous");
    printf("Victimes retenues : %d\n\n", total_victimes_retenues);
    printf("%*s%-*s Age %-*s\n", 7, "", LARGEUR_MAX_BARRE, "HOMMES", LARGEUR_MAX_BARRE, "FEMMES");

    /* ---- 2e passage : une ligne par age ---- */
    for (Chainon_age *chainon = tete; chainon != NULL; chainon = chainon->suivant) {
        int nb_hommes = afficher_hommes ? compter_victimes_age(chainon, MASCULIN, filtre_usager) : 0;
        int nb_femmes = afficher_femmes ? compter_victimes_age(chainon, FEMININ,  filtre_usager) : 0;

        if (nb_hommes == 0 && nb_femmes == 0) {
            continue;                   /* aucun blesse/tue/indemne a cet age : on saute la ligne */
        }

        double pourcentage_hommes = 100.0 * nb_hommes / total_victimes_retenues;
        double pourcentage_femmes = 100.0 * nb_femmes / total_victimes_retenues;

        int longueur_barre_hommes = nb_hommes * LARGEUR_MAX_BARRE / effectif_max;
        int longueur_barre_femmes = nb_femmes * LARGEUR_MAX_BARRE / effectif_max;

        /* Une valeur non nulle a toujours au moins un '#' visible */
        if (nb_hommes > 0 && longueur_barre_hommes == 0) longueur_barre_hommes = 1;
        if (nb_femmes > 0 && longueur_barre_femmes == 0) longueur_barre_femmes = 1;

        /* Cote hommes : pourcentage, espaces, puis barre alignee vers le centre */
        printf("%5.2f%% ", pourcentage_hommes);
        afficher_caracteres(LARGEUR_MAX_BARRE - longueur_barre_hommes, ' ');
        afficher_caracteres(longueur_barre_hommes, '#');

        /* Age au centre */
        printf(" %3d ", chainon->age);

        /* Cote femmes : barre puis espaces, puis pourcentage */
        afficher_caracteres(longueur_barre_femmes, '#');
        afficher_caracteres(LARGEUR_MAX_BARRE - longueur_barre_femmes, ' ');
        printf(" %5.2f%%\n", pourcentage_femmes);
    }

    printf("\n***************************************\n");
}
