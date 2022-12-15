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

/* ANALYSE COMPLEXITE : */
/* Donc analyse_arbre est en O(n) ce qui est super cool :D */




/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int recherche_espece_rec(arbre racine,char *espece, cellule_t** seq){
  if(racine == NULL){                                                         //O(1)
    return 1;                                                                 //O(1)
  }
  if(racine->droit == NULL && racine->gauche == NULL){                        //O(1)
    if(strcmp(racine->valeur, espece) == 0){                                  //O(1 + len(espece)) ~ O(1)
      return 0;                                                               //O(1)
    }
    else{
      return 1;                                                               //O(1)
    }
  }
  if(racine->gauche != NULL){                                                 //O(1)
    int rep = recherche_espece_rec(racine->gauche, espece, seq);              //au maximum : O(n) si l'arbre n'a que des arbres de 1 enfant, au minimum O(log2(n))
    if(rep == 0){                                                             //O(1)
      return 0;                                                               //O(1)
    }
  }
  if(racine->droit != NULL){                                                  //O(1)
    cellule_t *cel = malloc(sizeof(cellule_t));                               //O(1)
    cel->val = racine->valeur;                                                //O(1)
    *seq = cel;                                                               //O(1)
    int rep = recherche_espece_rec(racine->droit, espece, &cel->suivant);     //au maximum : O(n) si l'arbre n'a que des arbres de 1 enfant, au minimum O(log2(n))
    if(rep == 0){                                                             //O(1)
      return 0;                                                               //O(1)
    }
    else{
      free(cel);                                                              //O(1)
      *seq = NULL;                                                            //O(1)
    }
  }
  return 1;                                                                   //O(1)
}
/* ANALYSE COMPLEXITE : */
/* Donc dans le pire des cas la complexite est O(n) */


int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{
  return recherche_espece_rec(racine, espece, &(seq->tete));           // O(n)
}
/* ANALYSE COMPLEXITE : */
// O(n)


// ACTE3 :

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
    ajout_direct_espece(&(mon_arbre->droit), espece, seq->suivant);            //O(len(espece))
  }
  return;
}
// Complexite : O(len(seq))


int est_espece(arbre a){ //retourne un bool disant si l'arbre est une espece (n'as pas d'enfants)
  return (a->droit == NULL && a->gauche == NULL); // O(1)
}
// Complexite : O(1)


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
/* ANALYSE COMPLEXITE */
// Pour n, nombre d'elements de l'arbre.
// au pire des cas : O(n + len(seq)) , et au meilleur des cas : O(log2(n))


/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre a, FILE* fout) {
  if (a == NULL){
    return;
  }
  // On va utiliser la technique que vous nous avez conseilé pendant un td, celle de faire un tableau de taille 25000
  // car on sait que aucun fichier de tests n'a plus de 50 000 especes
  // Je tiens a preciser que ce code a été fait pendant un TD et donc qu'il risque de fortement ressembler a celui de nos collegues de TD.
  arbre *tab[25000];
  tab[0]=&a;
  // On met dans notre tableau notre arbre.
  // On va définir 3 variable qui vont permettre de nous donner les index des éléments dans le tableau que nous utilisons.
  int deb = 0;
  int niveau = 0;
  int fini = 0;
  int nb_elems = 1; //La taille fictive de notre tableau (tous les trucs qu'il nous reste a traiter.)
  // On va maintenant faire un parcours en largeur afin de pouvoir itérer profondeur par profondeur de notre arbre.
  while(!(nb_elems==0)){
    if (!((*tab[deb])->droit == NULL && (*tab[deb])->gauche == NULL)){ // Si les deux sous arbres ne sont pas vides alors on ajoute tab[deb]->val car c'est une caractéristiques.
      fprintf(fout,"%s ",(*tab[deb])->valeur);
    }
    if ((*tab[deb])->gauche != NULL){
      fini = fini + 1 %25000;
      tab[fini]=&(*tab[deb])->gauche;
      nb_elems++;
    }
    if ((*tab[deb])->droit != NULL){
      fini = fini + 1 %25000;
      tab[fini]=&(*tab[deb])->droit;
      nb_elems++;
    }
    nb_elems--;
    if(deb==niveau){
      niveau=fini;
      fprintf(fout,"\n");
    }
    deb++;
  }
}
/* ANALYSE COMPLEXITE */
// O(n) (nombre d'elements de l'arbre)


// Acte 4
//fonction secondaire
void ajout_direct_carac(arbre* a,char* carac){
  arbre nouv = nouveau_noeud();
  nouv->droit = *a;
  nouv->valeur = carac;
  *a = nouv;
}
//fonction principale
int ajouter_carac_rec(arbre* a, char* carac, cellule_t* seq) {
  if ((*a)->droit == NULL && (*a)->gauche == NULL)
  {
    if(est_dans_seq(seq, (*a)->valeur)){
      if(longueur_seq(seq) == 1){//il y a une seul espèc et c'est celle là
        ajout_direct_carac(a, carac);
        return 1;
      }
      else{
        return 1;
      }
    }
    else{
      return 0;
    }
  }
  if((*a)->droit != NULL && (*a)->gauche != NULL){
    int resg, resd;
    resg = ajouter_carac_rec(&((*a)->gauche), carac, seq);
    resd = ajouter_carac_rec(&((*a)->droit), carac, seq);
    if(resg + resd == longueur_seq(seq)){
      if(resg == 0 || resd == 0){
        return resg + resd;
      }
      else{
        ajout_direct_carac(a, carac);
        return resd + resg;
      }
    } 
    if(resd==0 || resd==0){
      return 0;
    }
    else{
      return resg + resd;
    }
  }
  if((*a)->gauche != NULL){ // (*a)->droit == NULL
    return ajouter_carac_rec(&((*a)->gauche), carac, seq);
  }
  else{
    return ajouter_carac_rec(&((*a)->droit), carac, seq);
  }
}


// fonction d'enrobage
int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
  ajout_direct_carac(a, carac);
  return 1;
  // liste_t l;
  // l.tete = seq;
  // printf("liste d'especes:\n");
  // affiche_liste(&l);
  // printf("\n");
  // printf("fonction ajouter_carac\n");
  if ((*a) == NULL){
    if (longueur_seq(seq) == 0)
    {
      ajout_direct_carac(a, carac);
      return 1;
    }
    else{
      return 0;
    }
  }
  //tout es normal: on lance la récursion
  if (ajouter_carac_rec(a, carac, seq) == 0){
    return 0;
  }
  else{
    return 1;
  }
}


// Acte 5
#define TAILLE_MAX 1000

int somme_colonne(int **correspondances,int index_to_sum, int nb_especes){
  int res = 0;
  for (int i = 0; i<nb_especes;i++){
    res += correspondances[i][index_to_sum];
  }
  return res;
}

int somme_ligne(int **correspondances,int index_to_sum, int nb_carac){
  int res = 0;
  for (int i = 0; i<nb_carac;i++){
    res += correspondances[index_to_sum][i];
  }
  return res;
}

void echange_colonne(int a,int b, int **correspondances, char **caracteristique, int nb_especes){
  for (int pos = 0; pos < nb_especes; pos++){
    if (correspondances[pos][a]!= correspondances[pos][b]){
      correspondances[pos][a]= !(correspondances[pos][a]);
      correspondances[pos][b]= !(correspondances[pos][b]);
    }
  }
  char *temp = caracteristique[a];
  caracteristique[a] = caracteristique[b];
  caracteristique[b] = temp; 
}
/*
void tri_espece(int nb_especes, char especes[100][50],int correspondances[100][50], int nb_carac, int nb_especes){
  int index_max = 0;
  int somme_max = 0;
  int somme_actuel = 0;
  for (int i=0; i<nb_especes;i++){
    for (int j=0; j<nb_especes;j++){
      somme_actuel = somme_ligne(correspondances,j,nb_carac);
      if (somme_actuel >= somme_max){
        somme_max = somme_actuel;
        index_max = j;
      }
    }
    echange_ligne(i,index_max,correspondances,especes,nb_carac);
    somme_max=0;
  }
}
void tri_carac(int nb_carac, char caracteristique[100][50],int correspondances[100][50], int nb_cara, int nb_especes){
  int index_max = 0;
  int somme_max = 0;
  int somme_actuel = 0;
  for (int i=0; i<nb_cara;i++){
    for (int j=0; j<nb_cara;j++){
      somme_actuel = somme_colonne(correspondances,j,nb_especes);
      if (somme_actuel >= somme_max){
        somme_max = somme_actuel;
        index_max = j;
      }
    }
    echange_colonne(i,index_max,correspondances,caracteristique,nb_cara);
    somme_max=0;
  }
}
*/
int lire_table(char* nom_fichier, char **especes, char **caracteristiques, int **correspondances, int* nb_especes, int* nb_carac){
  // On passe en arguments :

  // nom_fichier : le fichier dans lequelle il y a notre arbre
  // especes : un tableau de strings qui represente la liste des especes (les strings ont une taille max = 1000)
  // caracteristiques : un tableau de strings qui represente la liste des caracteristiques (les strings ont une taille max = 1000)
  // correspondances : un tableau de tableau de int qui represente les correspondances d'une caracteristiques pour une espece
  // exemple correspondances[0][0] == 1 -> espece[0] a la caracteristique caracteristiques[0]
  // nb_especes : un pointeur vers un int qui contient le nombre d'espece dans le tableau especes
  // nb_carac : un pointeur vers un int qui contient le nombre de caracteristiques dans le tableau caracteristiques.

  // Renvoie -1 si erreur, 1 si réussi.
  
  FILE *f = fopen(nom_fichier, "r") ;
  if (f == NULL) {
      printf("%s n'a pas pu être ouvert en lecture \n",nom_fichier) ;
      return -1 ;
  }
  
  fscanf(f, "%d", nb_especes);
  printf("Nombre d'especes : %d \n",(*nb_especes));
  

  printf("Les especes : \n");
  for (int i=0; i < (*nb_especes); i++){
    fscanf(f, "%s", especes[i]);
    printf("%s ",especes[i]);
  }
  printf("\n");

  fscanf(f, "%d", nb_carac);
  printf("Nombre de caracteristiques : %d \n",(*nb_carac));
  

  printf("Les caracteristiques : \n");
  for (int i=0; i < (*nb_carac); i++){
    fscanf(f, "%s", caracteristiques[i]);
    printf("%s ",caracteristiques[i]);
  }
  printf("\n");


  for (int i=0; i < (*nb_especes); i++){
    for (int j=0; j< (*nb_carac); j++){
      fscanf(f,"%d", &correspondances[i][j]);
      printf("%d ",correspondances[i][j]);
    }
    printf("\n");
  } 
  fclose(f);
  return 1;

}

void afficher_matrice(char **especes, char **caracteristiques, int **correspondances, int nb_especes, int nb_carac){
  printf("\n               | ");
  for(int j =0; j < nb_carac; j++){
    printf("%s | ",caracteristiques[j]);
  }
  printf("\n");
  for(int i  = 0; i < nb_especes; i++){
    printf("%s",especes[i]);
    for(int k = 0; k < (15 - (int) strlen(especes[i])); k++){
      printf(" ");
    }
    printf("| ");
    for(int j = 0; j < nb_carac; j++){
      printf("%d",correspondances[i][j]);
      for(int k = 0; k < (int) strlen(caracteristiques[j]); k++){
        printf(" ");
      }
      printf("| ");
    }
    printf("\n");
  }
}


