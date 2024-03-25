#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/* ------------------- CONSTANTES -------------------------*/

#define __MAX_NOMBRE_ALPHABET__ 50
#define MAX_LEN_FILENAME 50

/* ------------------ STRUCTURE ---------------------------*/
typedef struct Etat
{
    int number;
    bool accessible;
}Etat;

typedef struct  Transitions
{
    Etat *E_depart; // pointe sur un Etat qui est dans lesEtats
    Etat *E_arrive;
    char etiquete[__MAX_NOMBRE_ALPHABET__];
}Transitions;

typedef struct Automate
{
    int *etatInitiaux; // c'est le tableau contenant les états initiaux
    int *etatFinaux; // c'est le tableu contenant les états finaux
    Transitions *transition; // c'est le tableau contenant les transitions
    char *alphabet; // c'est le tableau contenant l'ensemble de tous les alphabets utilisées
    Etat *lesEtats;
}Automate;

/* -------------------------------------PROTOTYPES ----------------------------------------------*/

/*------------------ importerAutomate.c ---------------*/
void importerAutomate(Automate *autom, FILE *file, int *taille);
Automate retourneAutomateImporte(Automate autom, int *taille);

/*----------------- manipAutomate.c ------------------*/
void initAutomate(Automate *autom, int *taille);
void freeMemory(Automate *autom);
void getEtatInitFin(FILE *file, Automate *autom, int *taille, int isEtatInit); // isEtatInit: =1(si recuperation etat initiaux) ; =0(si récupération états finaux)
void ajouterAlphabet(Automate *autom, char *etiquete);
void ajoutEtatFinaux(Automate *autom, int *taille, int nouvEtatFinal);
void ajoutEtatInitaux(Automate *autom, int *taille, int nouvEtatIniatial);
bool isFinalState(Automate autom, int *taille, int state);

void ajoutTransition(Automate *automate, Transitions transition, int *nbTransition);
bool isTransitionExits(Automate autom, int *taille, Transitions transToAdd);
bool isInTab(int *tab, int taille, int value);

void ajoutEtat(Automate *autom, Transitions transition, int *taille);
Etat* getEtat(Automate *autom, int *taille, int number);

void copyAutomate(Automate *automDest, int *taille_automDest, Automate automSource, int *taille_automSource);
bool changerAutomate();

/*-----------------getInaccessibleState.c-------------*/
void trouverEtatInaccessible(Automate *autom, int *taille, int *EDep, int tailleT);

/*----------------- affichage.c ----------------------*/
void afficherAutomate(Automate *autom, int *taille);
void affEtatInitiaux(Automate *autom, int *taille);
void affEtatFinaux(Automate *autom, int *taille);
void affTransitions(Automate *autom, int *taille);
void afficherAlphabet(Automate *autom);
void menu(Automate *autom, int *taille);
void menuPrincipal();

/*---------------- generateDotImg.c ------------------*/
void genererDotImg(Automate *autom, int *taille, char *graphName);

/*---------------- estILEngendre.c -------------------*/
void testerMotsDansFichier(Automate *autom,  int *taille);
bool estEngendreRecursif(char* mot, int etatCourant, Automate *autom, int *taille);
bool estEngendre(char* mot, Automate *autom, int *taille);

// void estIlEngendre(Automate *autom, char *mot, int *taille, int *EDep, int tailleT, bool *isGeneretedBy);

/*---------------- supprimerEpsTrans.c -------------------*/
void automateSansEpsilone(Automate *autom, int *taille);

/*---------------- union2automates.c -------------------*/
Automate unionAutomate(Automate autom1, int *taille1, Automate autom2, int *taille2, int *tailleUnion);
bool launchUnionAutomate(Automate *autom1, int *taille1, Automate autom2, int *taille2);

/*---------------- etoile_automates.c -------------------*/
bool launchEtoileAutomate(Automate *autom, int *taille);
Automate etoile_Automate(Automate autom, int *taille, int *tailleEtoile);

/*---------------- produit2Automates.c -------------------*/
bool launchProdOfAutom(Automate *autom0, int *taille0, Automate autom1, int *taille1);
bool produit_Automate(Automate autom0, int *taille0, Automate autom1, int *taille1, int **EDep, int tailleEDep[2], int firstTime, Automate *automProduit, int *tailleProduit);
int* getNextStateFrom(int *curState, int nbCurState, Automate autom, int *taille, char etiquete, int *nb_nextStates);

/*---------------- determinationAutom.c -------------------*/
void determinerAutom(Automate autom, int *taille, int *EDep, int tailleEDep, int firstTime, Automate *automDetermine, int *taille_AutomDetermine);

/*---------------- minimiserAutom.c -------------------*/
Automate minimiserAutomate(Automate autom, int *taille, int *tailleAutomMinim);

#endif