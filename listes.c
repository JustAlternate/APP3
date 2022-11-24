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
  cellule_t *ancienne_tete = L->tete;
  cellule_t *nouv = malloc(sizeof(cellule_t));
  nouv->val = c;
  L->tete = nouv;
  nouv->suivant = ancienne_tete;
  return 1;
}

