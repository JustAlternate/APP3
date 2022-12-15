#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"

int DEBUG = 0;

int main(int argc, char* argv[])
{
    char *fichier = NULL;

    if (argc < 2) {
        fprintf (stderr, "Usage:  %s [-d] <fichier>\n", argv[0]);
        fprintf (stderr, "\n");
        fprintf (stderr, "Options:\n");
        fprintf (stderr, "\t-d\tmode debug\n");
        exit(1);
    }
    int arg=1;

    while (arg < argc) {
        if (!strncmp(argv[arg], "-d", 2)) {
            DEBUG = 1;
            arg++;
            continue;
        }
        if (argv[arg][0] == '-') {
            fprintf (stderr, "Option inconnue : '%s'\n", argv[arg]);
            exit(1);
        }
        if (fichier == NULL) {
            fichier = argv[arg];
            arg++;
            continue;
        }
        else {
            fprintf (stderr, "Trop de fichiers sur la ligne de commande : '%s'\n", argv[arg]);
            exit(1);
        }
    }

    debug ("Ouverture de %s\n", fichier);
    FILE* f = fopen (fichier, "r");
    if (!f) {
        fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", fichier);
        perror (fichier);
        exit(1);
    }

    arbre mon_arbre = lire_arbre (f);

    int nombre_especes; /* Ne pas initialiser ici, c'est analyse_arbre */
    int nombre_caract;  /* qui doit s'en charger */

    affiche_arbre (mon_arbre);

    analyse_arbre (mon_arbre, &nombre_especes, &nombre_caract);

    printf ("Nombre d'especes de l'arbre: %d\n", nombre_especes);
    printf ("Nombre de caractéristiques de l'arbre: %d\n", nombre_caract);
    int decalage = 0;

    print_arbre(mon_arbre,&decalage);
    char **especes = malloc(sizeof(char*)*100);
    char **caracteristiques = malloc(sizeof(char*)*100);
    int **correspondances = malloc(sizeof(int*)*100);

    for(int i = 0; i < 100; i++){
      especes[i] = malloc(sizeof(char)*50);
      caracteristiques[i] = malloc(sizeof(char)*50);
      correspondances[i] = malloc(sizeof(int)*50);
    }
    int nb_especes = 0;
    int nb_carac = 0;
    char *nom_fichier = "table_correspondance_exemple";
    lire_table(nom_fichier,especes,caracteristiques,correspondances,&nb_especes,&nb_carac);
    printf("j'affiche la matrice:");
    afficher_matrice(especes, caracteristiques, correspondances, nb_especes, nb_carac);
    printf("j'ai affiché");







    return 0;
}


