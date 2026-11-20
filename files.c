
FILE* openFile( const char* cy_crash_https://github.com/Assia494/Projet-Supmeca-D/securitytech_small.csv, const char*r ){
    fichier = fopen("cy_crash_tech_small.csv", "r+");
    
    if (fichier == NULL){
      printf("Ouverture du fichier impossible\n");
      printf("code d'erreur = %d \n", errno );
      printf("Message d'erreur = %s \n", strerror(errno) );
      exit(1);
    }

    return fichier; 
}


    
int lire_ligne_csv(FILE *fichier, LigneCSV *donnees) {
    char buffer[TAILLE_LIGNE_MAX];

    if (fichier == NULL || donnees == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), fichier) == NULL) {
        return 0; /* Fin de fichier (EOF) ou erreur de lecture */
    }

    /* Supprime le retour à la ligne (\n ou \r\n) en fin de chaîne */
    buffer[strcspn(buffer, "\n")] = '\0';

    /* Ignore les lignes vides éventuelles */
    if (buffer[0] == '\0') {
        return lire_ligne_csv(fichier, donnees);
    }

    /* Découpage des 9 debut_colonne séparés par ';' */
    char *debut_colonne;                                                          // pointe sur le debut de la colonne en cours de lecture
    char *courant = buffer;                                               // avance dans buffer au fur et à meusure qu'on decope les points virgules
    int index_colonne = 0;

    /* Initialisation par défaut */
    donnees->year = 0;
    donnees->collision_id[0] = '\0';
    donnees->vehicle_id[0] = '\0';
    donnees->location = 0;
    donnees->user_type = 0;
    donnees->severity = 0;
    donnees->gender = 0;
    donnees->birth_year = 0;
    donnees->purpose = -1;

    while (index_colonne < 9) {
        debut_colonne = courant;
        char *point_virgule = strchr(courant, ';');

        if (point_virgule != NULL) {
            *point_virgule = '\0';
            courant = point_virgule + 1;
        } 
        
        else if (index_colonne < 8) {
            /* Moins de 9 colonnes trouvées sur la ligne */
            return -1;
        } 
        
        else {
            courant = NULL;
        }

        /* Retire d'éventuels espaces en début de debut_colonne (ex: " A01") */
        while (*debut_colonne == ' ' || *debut_colonne == '\t') {
            debut_colonne++;
        }

        switch (index_colonne) {
            case 0:
                donnees->year = atoi(debut_colonne);                               //atoi -> convertit une chaîne de caractères en un entier de type int
                break;
            case 1:
                strncpy(donnees->collision_id, debut_colonne, TAILLE_ID_MAX - 1);
                donnees->collision_id[TAILLE_ID_MAX - 1] = '\0';
                break;
            case 2:
                strncpy(donnees->vehicle_id, debut_colonne, TAILLE_ID_MAX - 1);
                donnees->vehicle_id[TAILLE_ID_MAX - 1] = '\0';
                break;
            case 3:
                donnees->location = atoi(debut_colonne);
                break;
            case 4:
                donnees->user_type = atoi(debut_colonne);
                break;
            case 5:
                donnees->severity = atoi(debut_colonne);
                break;
            case 6:
                donnees->gender = atoi(debut_colonne);
                break;
            case 7:
                donnees->birth_year = atoi(debut_colonne);
                break;
            case 8:
                if(*debut_colonne == '\0'){
                    donnees->purpose = -1;
                }

                else{
                    donnees->purpose = atoi(debut_colonne);
                }
                break;
        }

        index_colonne++;
    }

    return 1;
}

















































































        
  
