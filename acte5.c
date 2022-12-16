#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"



/*





POUR LANCER L'ACTE 5 FAIRE ./acte5 table_correspondance_exemple





 */





int DEBUG = 0;

//O(n)
void sequence_de_carac(int id_espece, liste_t *seq, char **caracteristiques, int **correspondances, int nb_carac){
  for (int i = 0; i < nb_carac; i++) //O(n)
  {
    if (correspondances[id_espece][i] == 1) //O(1)
    {
      ajouter_tete(seq, caracteristiques[i]); //O(1)
    }
  }
}

int main(int argc, char* argv[]){
    if (argc < 2) {
        fprintf (stderr, "Usage: donner le nom de votre fichier avec votre tableau");
        fprintf (stderr, "\n");
        exit(1);
    }

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
    char *nom_fichier = argv[1];
    lire_table(nom_fichier,especes,caracteristiques,correspondances,&nb_especes,&nb_carac);
    printf("j'affiche la matrice:");
    afficher_matrice(especes, caracteristiques, correspondances, nb_especes, nb_carac);
    
    tri_espece(nb_carac,especes,correspondances,nb_especes);
    tri_carac(nb_carac,caracteristiques,correspondances,nb_especes);

    printf("j'affiche la matrice triée :");
    afficher_matrice(especes, caracteristiques, correspondances, nb_especes, nb_carac);
    
    arbre final = NULL;
    liste_t liste;
    init_liste_vide(&liste);
    int p = 0; //pour le décalage
    for (int i = nb_especes - 1; i > -1; i--) //O(n)
    {
      liberer_liste(&liste); //O(n)
      sequence_de_carac(i, &liste, caracteristiques, correspondances, nb_carac); //O(n)
      ajouter_espece(&final, especes[i], liste.tete); // O(n + len(seq))
    }
    //au final: O(n(n + len(seq))) ~~~~ O(n²)
    printf("On affiche l'arbre dans le terminal avec notre super fonction : \n");
    print_arbre(final, &p);

    return 0;
}


