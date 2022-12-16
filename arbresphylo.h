#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include "listes.h"


/* Analyse un arbre: doit mettre à jour le nombre d'espèces et de 
 * caractéristiques.
 */
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac);

/* Recherche une espèce dans l'arbre et remplit seq avec la séquence de ses 
 * caractéristiques.
 *
 * Doit retourner 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq);


int ajouter_espece (arbre* racine, char *espece, cellule_t* seq);

void afficher_par_niveau(arbre racine, FILE* fout);

// on considère qu'il n'est pas possible
// d'insérer une caractéristique à un arbre vide, ni d'insérer une caractéristique
// qui n'est possédée par aucune espèce déjà présente dans l'arbre (pour ce
// cas-là, ajout_espece fait l'affaire). Ceci permet d'éviter d'avoir à ajouter
// des noeuds caractéristique sans enfant qui seraient confondues avec des
// espèces/feuilles.
int ajouter_carac(arbre* a, char* carac, cellule_t* seq);
 
int lire_table(char* nom_fichier, char **especes, char **caracteristiques, int **correspondances, int* nb_especes, int* nb_carac);

int somme_colonne(int **correspondances,int index_to_sum, int nb_carac);
int somme_ligne(int **correspondances,int index_to_sum, int nb_carac);

void afficher_matrice(char **especes, char **caracteristiques, int **correspondances, int nb_especes, int nb_carac);

void echange_colonne(int a,int b, int **correspondances, char **caracteristique, int nb_especes);
void echange_ligne(int a,int b, int **correspondances, char **especes, int nb_carac);
void tri_espece(int nb_carac, char **especes,int **correspondances, int nb_especes);

void tri_carac(int nb_carac, char **caracteristique,int **correspondances, int nb_especes);
 
#endif
