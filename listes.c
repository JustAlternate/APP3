#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
  L->tete = NULL;
}

void liberer_liste(liste_t* L) {
  if (L->tete == NULL){
    return;
  }
  cellule_t *cur;
  cur = L->tete;
  cellule_t *suiv = cur->suivant;
  L->tete = NULL;
  while(suiv != NULL){
    free(cur);
    cur = suiv;
    suiv = suiv->suivant;
  }
  free(cur);
    
}

int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
  if (L->tete == NULL){
    L->tete = malloc(sizeof(cellule_t));
    L->tete->val = c;
  }
  else{
    cellule_t *ancienne_tete = L->tete;
    cellule_t *nouv = malloc(sizeof(cellule_t));
    nouv->val = c;
    L->tete = nouv;
    nouv->suivant = ancienne_tete;
  }
  return 1;
}

void affiche_liste(liste_t* L){
  cellule_t *cur = L->tete;
  while(cur!=NULL){
    printf("%s ",cur->val);
    cur = cur->suivant;
  }
}

int longueur_seq(cellule_t* seq){
  int i = 0;
  for (i = 0; seq != NULL; i++)
  {
    seq = seq->suivant;
  }
  return i;
}

int est_dans_seq(cellule_t* seq, char* carac){
  if(seq==NULL){
    return 0; // FALSE
  }
  else{
    if(strcmp(carac, seq->val) == 0){
      return 1; // TRUE
    }
    else{
      return est_dans_seq(seq->suivant, carac);
    }
  }
}
