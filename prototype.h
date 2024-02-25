#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

/* ------------------- CONSTANTES -------------------------*/

#define __MAX_NOMBRE_ALPHABET__ 50

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

/*----------------- manipAutomate.c ------------------*/
void initAutomate(Automate *autom, int *taille);
int getEtatInitFin(FILE *file, Automate *autom, int isEtatInit); // isEtatInit: =1(si recuperation etat initiaux) ; =0(si récupération états finaux)
void ajouterAlphabet(Automate *autom, char *etiquete);
void ajoutTransition(Automate *automate, Transitions transition, int *nbTransition);
void freeMemory(Automate *autom);

void ajoutEtat(Automate *autom, Transitions transition, int *taille);
Etat* getEtat(Automate *autom, int *taille, int number);

/*-----------------getInaccessibleState.c-------------*/
void trouverEtatInaccessible(Automate *autom, int *taille, int *EDep, int tailleT);

/*----------------- affichage.c ----------------------*/
void afficherAutomate(Automate *autom, int *taille);
void affEtatInitiaux(Automate *autom, int *taille);
void affEtatFinaux(Automate *autom, int *taille);
void affTransitions(Automate *autom, int *taille);
void afficherAlphabet(Automate *autom);
void menu(Automate *autom, int *taille);

/*---------------- generateDotImg.c ------------------*/
void genererDotImg(Automate *autom, int *taille);

/*---------------- estILEngendre.c -------------------*/
void estIlEngendre(Automate *autom, char *mot, int *taille, int *EDep, int tailleT, bool *isGeneretedBy);
void testerMotsDansFichier(Automate *autom,  int *taille);


#endif