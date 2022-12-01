#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"


void analyse_arbre_rec(arbre racine, int* nb_esp, int *nb_carac){
  if (racine == NULL){
    return;
  }
  if (racine->gauche == NULL && racine->droit == NULL){            // O(1)
    (*nb_esp)++;                                                   // O(1)
    return;
  }
  (*nb_carac)++;                                                   // O(1)

  analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);          
  analyse_arbre_rec(racine->droit, nb_esp, nb_carac);              
  return;

}

void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
  *(nb_esp) = 0;                                                   // O(1)
  *(nb_carac) = 0;                                                 // O(1)
  analyse_arbre_rec(racine,nb_esp,nb_carac);                       // O(n) (on fait n fois la récurrence)
}

// Donc analyse_arbre est en O(n) ce qui est super cool :D




/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int recherche_espece_rec(arbre racine,char *espece, cellule_t** seq){
  if(racine == NULL){
    return 1;
  }
  if(racine->droit == NULL && racine->gauche == NULL){
    if(strcmp(racine->valeur, espece) == 0){
      printf("on a trouvé l'espece: %s\n", racine->valeur);
      return 0;
    }
    else{
      return 1;
    }
  }
  if(racine->gauche != NULL){
    int rep = recherche_espece_rec(racine->gauche, espece, seq);
    if(rep == 0){
      return 0;
    }
  }
  if(racine->droit != NULL){
    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->val = racine->valeur;
    *seq = cel;
    int rep = recherche_espece_rec(racine->droit, espece, &cel->suivant);
    if(rep == 0){
      return 0;
    }
    else{
      free(cel);
      *seq = NULL;
    }
  }
  return 1;
}

int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{
  return recherche_espece_rec(racine, espece, &(seq->tete));
}

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
// on fait d'abors deux fonction intemédiaire:
void ajout_direct_espece(arbre *a, char *espece, cellule_t* seq){
  arbre mon_arbre = malloc(sizeof(arbre));
  if (seq == NULL)
  {
    mon_arbre->valeur = espece;
    (*a) = mon_arbre;
  }
  else{
    mon_arbre->valeur = seq->val;
    (*a) = mon_arbre;
    ajout_direct_espece(&(mon_arbre->droit), espece, seq->suivant);
  }
  return;
}

int est_espece(arbre a){ //retourne un bool disant si l'arbre est une espece (n'as pas d'enfants)
  return (a->droit == NULL && a->gauche == NULL); // O(1)
}

int ajouter_espece (arbre* a, char *espece, cellule_t* seq) { // c'est recursif
  if (*a == NULL)
  {
    ajout_direct_espece(a, espece, seq);
    return 0;
  }
  else{
    if(est_espece(*a)){ // on est sur une espece il n'y a plus despeces plus bas 
      if (seq == NULL){ // on a deux espèces avec exactement les mêmes caractéristique: erreur
        printf("ERREUR: impossible d'ajouter l'espece, une autre espece a déjà les mêmes caractéristiques.\n");
        return 1;
      }
      else{ //on ajoute la nouvelle espèce et on décale l'anciennes
        arbre mon_arbre = malloc(sizeof(arbre));
        arbre ancienne_espece = (*a);
        mon_arbre->valeur = seq->val;
        *a = mon_arbre;
        mon_arbre->gauche = ancienne_espece;
        ajout_direct_espece(&(mon_arbre->droit), espece, seq->suivant);
        return 0;
      }
    }
    else{// a n'est pas une espece
      if (seq == NULL){//plus de caractéristique à vérifier: on va a gauche.
        return ajouter_espece(&((*a)->gauche), espece, seq);
      }
      if (strcmp((*a)->valeur,seq->val) == 0){//l'espece a la caractéristique:
        int ret = ajouter_espece(&((*a)->droit), espece, seq->suivant);
        free(seq->val);
        return ret;
      }
      else{
        return ajouter_espece(&((*a)->gauche), espece, seq);
      }
    }
  }

}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
   printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
