#include "prototype.h"

void importerAutomate(Automate* autom, FILE *file, int* taille)
{
    int iTrans = 0, isEndOfTransition = 0;
    Transitions *transTemp;

    rewind(file);

    // fseek(file, 65, SEEK_SET); //Pour sauter l'entête du fichier

    //lecture du fichier en stockant les transitions, les états initiaux et les états finaux
    while(!feof(file))
    {
        isEndOfTransition = (fgetc(file) == '>')? 1 : 0;

        fseek(file, -1, SEEK_CUR);

        if(isEndOfTransition == 1) 
        {
            fseek(file, 3, SEEK_CUR); // 3: ce déplacement est nécessaire pour sauter le char '>' et le '\n'

            taille[1] = getEtatInitFin(file, autom, 1); // pour l'ajout des états initiaux

            if (!feof(file))
                taille[2] = getEtatInitFin(file, autom, 0); //pour l'ajout des états finaux 

        }
        else
        {   
            transTemp = (Transitions*)malloc(sizeof(Transitions));
            transTemp[0].E_arrive = (Etat*)malloc(sizeof(Etat));
            transTemp[0].E_depart = (Etat*)malloc(sizeof(Etat));
            
            if(transTemp==NULL || transTemp[0].E_arrive==NULL || transTemp[0].E_depart==NULL)
            {
                exit(EXIT_FAILURE);
            }
 
            fscanf(file, "%d %d %s", &(transTemp->E_depart->number), &(transTemp->E_arrive->number), transTemp->etiquete);

            ajoutTransition(autom, *transTemp, taille);
            ajouterAlphabet(autom, (*transTemp).etiquete);

            fseek(file, 2, SEEK_CUR); //retour à la ligne

            free(transTemp); // libérer la transition temporaire

        }     

    }

    //synchroniser les Transitions avec les états, càd faire pointer E_depart et E_arrive vers l'état qui lui correspond dans le tableau lesEtats 

    for (int  i = 0; i < taille[0]; i++)
    {
        autom->transition[i].E_depart = getEtat(autom, taille, autom->transition[i].E_depart->number);
        (*autom).transition[i].E_arrive = getEtat(autom, taille, autom->transition[i].E_arrive->number);
    }

    //Vérifier les accessibilités des états et les marquer s'il sont accessible (Etats initiaux toujours accessibles)
    trouverEtatInaccessible(autom, taille, autom->etatInitiaux, taille[1]);       
}
