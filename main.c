#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

int DEBUG = 0;

//O(n)
void sequence_de_carac(int id_espece, liste_t *seq, char **caracteristiques, int **correspondances, int nb_carac){
  //printf("l'id : %d\n", id_espece);
  for (int i = 0; i < nb_carac; i++) //O(n)
  {
    //printf("on test %s, c'est: %d\n", caracteristiques[i], correspondances[id_espece][i]);
    if (correspondances[id_espece][i] == 1) //O(1)
    {
      ajouter_tete(seq, caracteristiques[i]); //O(1)
      //printf("ça marche");
      // printf("on a ajouté %s\n", caracteristiques[i]);
    }
    //printf("voici la séquence:\n");
    //affiche_liste(seq);
  }
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
    
    arbre final = NULL;
    //final->droit = NULL;
    //final->gauche = NULL;
    //final->valeur = " coucou ";
    liste_t liste;
    init_liste_vide(&liste);
    //printf("on start la boucle\n");
    int p = 0; //pour le décalage
    for (int i = nb_especes - 1; i > -1; i--) //O(n)
    {
      //printf("\ndans la boooooucle\n");
      //printf("l'espece du moment: %s\n", especes[i]);
      //printf("on montre la séquence avant free:\n  ");
      //affiche_liste(&liste);
      liberer_liste(&liste); //O(n)
      //printf("on montre la séquence apres free:\n  ");
      //affiche_liste(&liste);
      //printf("on commence la séquence.\n");
      sequence_de_carac(i, &liste, caracteristiques, correspondances, nb_carac); //O(n)
      //printf("on montre la séquence:\n  ");
      //affiche_liste(&liste);
      //printf("on a montré la séquence\non ajoute espece\n");
      ajouter_espece(&final, especes[i], liste.tete); // O(n + len(seq))
      //printf("on a ajouté espece\n");
      //printf("l'espece: %s \n", especes[i]);
      //print_arbre(final, &p);
      //printf("on réaffiche la list\n  ");
      //affiche_liste(&liste);
    }
    //au final: O(n(n + len(seq))) ~~~~ O(n²)
    print_arbre(final, &p);

    return 0;
}


