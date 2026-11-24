#include <stdio.h>
#include <stdlib.h>
#include "year_data.h"
#include "csv_parser.h"
#include "initialisation.h"

void charger_year_data(const char *chemin_csv, StatAnnee tab[20])
{
    FILE *fichier = fopen(chemin_csv, "r");

    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier CSV.\n");
        exit(1);
    }

    /* Initialisation des statistiques */
    for (int i = 0; i < 20; i++)
    {
        tab[i].nb_accidents = 0;
        tab[i].indemnes = 0;
        tab[i].morts = 0;
        tab[i].blesses_graves = 0;
        tab[i].blesses_legers = 0;
    }

    /* Tableau contenant les accidents déjà rencontrés */
    year_collision_id accidents_vus[100000];
    int nb_vus = 0;

    LigneCSV ligne;
    int resultat;

    /* Lecture du fichier CSV */
    while ((resultat = lire_ligne_csv(fichier, &ligne)) == 1)
    {
        /* On ne garde que les années entre 2005 et 2024 */
        if (!verif_year(ligne.year, 2005, 2024))
        {
            continue;
        }

        int indice = indiceAnnee(ligne.year);

        /* Vérification si l'accident a déjà été compté */
        int deja_compte = 0;

        for (int i = 0; i < nb_vus; i++)
        {
            if (accidents_vus[i].year == ligne.year &&
                accidents_vus[i].collision_id == ligne.collision_id)
            {
                deja_compte = 1;
                break;
            }
        }

        /* Si l'accident n'a pas encore été rencontré */
        if (deja_compte == 0)
        {
            if (nb_vus >= 100000)
            {
                printf("Erreur : trop d'accidents dans le fichier.\n");
                fclose(fichier);
                exit(1);
            }

            accidents_vus[nb_vus].year = ligne.year;
            accidents_vus[nb_vus].collision_id = ligne.collision_id;

            nb_vus++;

            tab[indice].nb_accidents++;
        }

        /* Comptage des victimes selon leur gravité */
        switch (ligne.severity)
        {
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

    if (resultat == -1)
    {
        printf("Erreur lors de la lecture du fichier CSV.\n");
    }

    fclose(fichier);
}
