#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

int DEBUG = 0;

liste_t sequence_de_carac(int id_espece, char **especes, char **caracteristiques, int **correspondances, int nb_especes, int nb_carac){
  liste_t lc = malloc(sizeof(cellule_t));
  for (int i = 0; i < nb_carac; i++)
  {
    if(caracteristiques[id_espece][i]){
      ajouter_tete(lc, caracteristiques[i]);
    }
  }
  return lc;
}

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


    //CREER ARBRE EN PNG + AFFICHER DANS LE TERM :
    /*

    arbre mon_arbre = lire_arbre (f);

    int nombre_especes; // Ne pas initialiser ici, c'est analyse_arbre
    int nombre_caract;  // qui doit s'en charger 

    affiche_arbre (mon_arbre);

    analyse_arbre (mon_arbre, &nombre_especes, &nombre_caract);

    printf ("Nombre d'especes de l'arbre: %d\n", nombre_especes);
    printf ("Nombre de caractéristiques de l'arbre: %d\n", nombre_caract);
    int decalage = 0;

    print_arbre(mon_arbre,&decalage);

    */

    // LANCER ACTE 5
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
    
    tri_espece(nb_carac,especes,correspondances,nb_especes);
    tri_carac(nb_carac,caracteristiques,correspondances,nb_especes);

    printf("j'affiche la matrice triée :");
    afficher_matrice(especes, caracteristiques, correspondances, nb_especes, nb_carac);
    
    arbre final;
    liste_t liste;
    for (int i=nb_especes;i>-1;i--){

      
      init_liste_vide(&liste);
      for(int j=nb_carac;j>-1;j--){
        if (correspondances[i][j]){
          printf("cara accepté : %s\n",caracteristiques[j]);
          ajouter_tete(&liste, caracteristiques[j]);
        }
      }

      ajouter_espece(&final, especes[i], liste.tete);
      printf("%s ",especes[i]);

    }
    affiche_arbre(final);

    return 0;
}


