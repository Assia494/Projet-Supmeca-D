#include <stdio.h>
#include <stdlib.h>
#include "year_data.h"
#include "csv_parser.h"
#include "initialisation.h"

void charger_year_data(const char *chemin_csv, StatAnnee tab[20]) {

    FILE *fichier = fopen(chemin_csv, "r");

    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier CSV.\n");
        exit(1);
    }

    // Initialisation du tableau
    for (int i = 0; i < 20; i++) {
        tab[i].nb_accidents = 0;
        tab[i].indemnes = 0;
        tab[i].morts = 0;
        tab[i].blesses_graves = 0;
        tab[i].blesses_legers = 0;
    }

    // Tableau dynamique des accidents déjà comptabilisés
    year_collision_id *accidents_vus = NULL;
    int nb_vus = 0;

    LigneCSV ligne;

    int resultat;

    while ((resultat = lire_ligne_csv(fichier, &ligne)) == 1) {

        // Vérification de l'année
        if (!verif_year(ligne.year, 2005, 2024)) {
            continue;
        }

        int indice = indiceAnnee(ligne.year);

        // Recherche de l'accident dans les accidents déjà rencontrés
        int deja_compte = 0;

        for (int i = 0; i < nb_vus; i++) {

            if (accidents_vus[i].year == ligne.year && accidents_vus[i].collision_id == ligne.collision_id) {

                deja_compte = 1;
                break;
            }
        }

        // Si l'accident n'a pas encore été comptabilisé
        if (deja_compte == 0) {

            year_collision_id *temp = realloc(accidents_vus,(nb_vus + 1) * sizeof(year_collision_id));

            if (temp == NULL) {
                free(accidents_vus);
                fclose(fichier);
                exit(1);
            }

            accidents_vus = temp;

            accidents_vus[nb_vus].year = ligne.year;
            accidents_vus[nb_vus].collision_id = ligne.collision_id;

            nb_vus++;

            tab[indice].nb_accidents++;
        }

        // Comptabilisation de chaque victime
        switch (ligne.severity) {

            case INDEMNE:
                tab[indice].indemnes++;
                break;

            case TUE:
                tab[indice].morts++;
                break;

            case BLESSE_GRAVE:
                tab[indice].blesses_graves++;
                break;

            case BLESSE_LEGER:
                tab[indice].blesses_legers++;
                break;
        }
    }

    // Gestion d'une éventuelle erreur de lecture
    if (resultat == -1) {
        printf("Erreur lors de la lecture du fichier CSV.\n");
    }

    free(accidents_vus);

    fclose(fichier);
}



void afficher_stats_annee(StatAnnee tab[20], int annee)
{
    if (!verif_year(annee, 2005, 2024))
    {
        printf("Annee invalide.\n");
        return;
    }

    int indice = indiceAnnee(annee);

    printf("\n**********STATISTIQUES DE L'ANNEE %d **********\n", annee);

    printf("Nombre d'accidents : %d\n", tab[indice].nb_accidents);

    printf("Nombre d'usagers indemnes : %d\n", tab[indice].indemnes);

    printf("Nombre de personnes tuees : %d\n", tab[indice].morts);

    printf("Nombre de blesses graves : %d\n", tab[indice].blesses_graves);

    printf("Nombre de blesses legers : %d\n", tab[indice].blesses_legers);

    printf("**************************************************\n");
}




void menu_year_data(StatAnnee tab[20]) {
    int choix;
    int continuer = 1;

    while (continuer) {
        printf("\n****** MENU YEAR_DATA ******\n");
        printf("Entrez une annee entre 2005 et 2024\n");
        printf("pour afficher ses statistiques.\n");
        printf("Entrez 0 pour quitter.\n");
        printf("Votre choix : ");

        /* scanf renvoie 1 si un entier a bien ete lu */
        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide : veuillez entrer un nombre.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();

        if (choix == 0) {
            printf("Fin du mode YEAR_DATA.\n");
            continuer = 0;
        }
        else if (verif_year(choix, 2005, 2024)) {
            afficher_stats_annee(tab, choix);
        }
        else {
            printf("Annee invalide : elle doit etre comprise entre 2005 et 2024.\n");
        }
    }
}
