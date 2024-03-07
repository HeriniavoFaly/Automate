#include "prototype.h"

void initAutomate(Automate* autom, int *taille)
{
    (*autom).transition = NULL;
    (*autom).etatInitiaux = NULL;
    (*autom).etatFinaux = NULL;
    autom->alphabet = NULL;
    autom->lesEtats = NULL;
}

void freeMemory(Automate* autom)
{
    free((*autom).etatFinaux);
    free((*autom).etatInitiaux);
    free((*autom).transition);
    free(autom->alphabet);
    free(autom->lesEtats);

    printf("Liberation memoire avec succes....");
}

int getEtatInitFin(FILE *file, Automate *autom, int isEtatInit) // isEtatInit: =1(si recuperation etat initiaux) ; =0(si récupération états finaux)
{
    char curChar = ' ';
    char temp[2] = "";
    int nbEtatExistant = 0;

    while((curChar = fgetc(file))!= '\n' && !feof(file))
    {
        if(curChar != ' ')
        {
            temp[0] = curChar;
            temp[1] = '\0';

            if(isEtatInit) // si on est sur le point de lire les états initiaux
            {
                (*autom).etatInitiaux = (int*)realloc((*autom).etatInitiaux, (++(nbEtatExistant)) * sizeof(int));

                if((*autom).etatInitiaux == NULL)
                    exit(EXIT_FAILURE);

                autom->etatInitiaux[nbEtatExistant-1] = atoi(temp);
            }
            else
            {
                (*autom).etatFinaux  = (int*)realloc((*autom).etatFinaux, (++(nbEtatExistant)) * sizeof(int));

                if((*autom).etatFinaux == NULL)
                    exit(EXIT_FAILURE);

                autom->etatFinaux[nbEtatExistant-1] = atoi(temp);
            }
        }
    }
    return nbEtatExistant;
}

void ajouterAlphabet(Automate *autom, char *etiquete) // A: alphabet
{
    if(autom->alphabet == NULL) // s'il n'y a encore rien dans la chaîne alphabet
    {
        autom->alphabet = (char*)malloc(2* sizeof(char));
        autom->alphabet[0] = ' ';
        autom->alphabet[1] = '\0';
    }
        
    int j = strlen(autom->alphabet); // s'il y a une chaîne dans alphabet, on récupère sa longueur
    char temp[2];

    for (int i = 0; i < strlen(etiquete); i++)
    {
        //convertir un caractère en chaîne
        temp[0] = etiquete[i];
        temp[1] = '\0';

        if((strcspn(autom->alphabet, temp)) == strlen(autom->alphabet)) // verifie si etiquete[i] n'est pas encore dans alphabet
        {
            autom->alphabet = (char*)realloc(autom->alphabet, (++j) * sizeof(char));

            if (autom->alphabet == NULL)
                exit(EXIT_FAILURE);            

            autom->alphabet[j-1] = etiquete[i];
            autom->alphabet[j] = '\0';
        }
    }  

}

void ajoutTransition(Automate *automate, Transitions transition, int *taille)
{
    //augmentation de la taille du tableau transition
    (*automate).transition = (Transitions*)realloc((*automate).transition, (++taille[0])*sizeof(Transitions));

    if((*automate).transition == NULL)
    {
        printf("Reallocation de la mémoire a echoue...");
        freeMemory(automate);
        exit(EXIT_FAILURE);
    }

    //allocation des états dans la nouvelle transition
    automate->transition[taille[0]-1].E_arrive = (Etat*)calloc(1,sizeof(Etat));
    automate->transition[taille[0]-1].E_depart = (Etat*)calloc(1,sizeof(Etat));

    if((*automate).transition->E_arrive == NULL || (*automate).transition->E_depart == NULL)
    {
        printf("Reallocation de la mémoire pour les Etats a echoue... ");
        freeMemory(automate);
        exit(EXIT_FAILURE);
    }

    //ajout nouveau état s'il existe
    ajoutEtat(automate, transition, taille);

    //récupération des numéros des états dans une transition
    automate->transition[taille[0]-1].E_depart->number = transition.E_depart->number;
    (*automate).transition[taille[0]-1].E_arrive->number = transition.E_arrive->number;
    strcpy(automate->transition[taille[0]-1].etiquete, transition.etiquete);

}

void ajoutEtat(Automate *autom, Transitions transition, int *taille)
{
    bool E_depart_est_nouveau = true;
    bool E_arrive_est_nouveau = true;

    //tester si l'état de depart existe déjà si oui on sort
    for(int i=0; (i<taille[3])&& taille[3]!=0; i++)
    {
        if(autom->lesEtats[i].number == transition.E_depart->number)
        {
            E_depart_est_nouveau = false;
            break;
        }
    }

    //tester si l'état d'arrivé existe déjà si oui on sort
    for (int i = 0; (i < taille[3])&& taille[3]!=0; i++)
    {
        if(autom->lesEtats[i].number == transition.E_arrive->number)
        {
            E_arrive_est_nouveau = false;
            break;
        }        
        
    }

    //ajout de l'état de depart s'il n'existe pas encore
    if(E_depart_est_nouveau||taille[3]==0)
    {
        autom->lesEtats = (Etat*)realloc(autom->lesEtats, (++taille[3])*sizeof(Etat));

        if((*autom).lesEtats == NULL)
        {
            printf("Reallocation de la mémoire a echoue...");
            freeMemory(autom);
            exit(EXIT_FAILURE);
        }

        autom->lesEtats[taille[3]-1].accessible = false;
        autom->lesEtats[taille[3]-1].number = transition.E_depart->number;
    }

    //ajout de l'état d'arrivé s'il n'existe pas encore

    if (E_arrive_est_nouveau)
    {
        autom->lesEtats = (Etat*)realloc(autom->lesEtats, (++taille[3])*sizeof(Etat));

        if((*autom).lesEtats == NULL)
        {
            printf("Reallocation de la mémoire a echoue...");
            freeMemory(autom);
            exit(EXIT_FAILURE);
        }
                
        autom->lesEtats[taille[3]-1].accessible = false;
        autom->lesEtats[taille[3]-1].number = transition.E_arrive->number;
    }

}


// fonction qui retourne l'adresse d'un état qui correspond au numéro number
Etat* getEtat(Automate *autom, int *taille, int number)
{
    for(int i=0; i<taille[3]; i++)
    {
        if(autom->lesEtats[i].number == number)
        {
            return &(autom->lesEtats[i]);
        }

    }
}