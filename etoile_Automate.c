#include "prototype.h"

bool launchEtoileAutomate(Automate *autom, int *taille)
{
    Automate etoileAutom;
    int tailleEtoile[4] = {0};

    etoileAutom = etoile_Automate(*autom, taille, tailleEtoile);

    genererDotImg(&etoileAutom, tailleEtoile, "Automate_Etoile");
    if (changerAutomate())
    {
        printf("***** ON TRAVAILLE MAINTENANT AVEC L'ETOILE D'UN AUTOMATE *****\n");
        copyAutomate(autom, taille, etoileAutom, tailleEtoile);
        return true;
    }
    // freeMemory(&etoileAutom);
    return false; // s'il ne veut pas utiliser l'automate etoile
}

Automate etoile_Automate(Automate autom, int *taille, int *tailleEtoile)
{
     FILE *fileEtoile = NULL, *fileEtoileRead = NULL;
    int nouvEtats[2] = {-1, -2}, nouvEtatInit = -3, nouvEtatFinal = -4;
    Automate etoileAutom;
    // int tailleUnion[4] = {0};

    fileEtoile = fopen("etoileAutom.txt", "w");
    fileEtoileRead = fopen("etoileAutom.txt", "r");

    if(fileEtoile != NULL && fileEtoileRead != NULL)
    {
        int i;
        for (i = 0; i < taille[0]; i++)
            fprintf(fileEtoile, "%d %d %s\n", autom.transition[i].E_depart->number, autom.transition[i].E_arrive->number, autom.transition[i].etiquete);
        
        for(i=0; i < taille[1]; i++)
            fprintf(fileEtoile, "%d %d %s\n", nouvEtats[0], autom.etatInitiaux[i], "`");

        for (i = 0; i < taille[2]; i++)
            fprintf(fileEtoile, "%d %d %s\n", autom.etatFinaux[i],nouvEtats[1], "`");
        
        fprintf(fileEtoile, "%d %d %s\n", nouvEtats[1], nouvEtatFinal, "`");
        fprintf(fileEtoile, "%d %d %s\n", nouvEtatInit,nouvEtats[0], "`");
        fprintf(fileEtoile, "%d %d %s\n", nouvEtats[1],nouvEtats[0], "`");
        fprintf(fileEtoile, "%d %d %s\n", nouvEtatInit,  nouvEtatFinal, "`");

        fprintf(fileEtoile, ">\n");
        //etat initial
        fprintf(fileEtoile, "%d\n", nouvEtatInit);

        //etats finaux
        fprintf(fileEtoile, "%d", nouvEtatFinal);
    
        
        fclose(fileEtoile);

        initAutomate(&etoileAutom, tailleEtoile);
        importerAutomate(&etoileAutom, fileEtoileRead, tailleEtoile);
        fclose(fileEtoileRead);

        // automateSansEpsilone(&etoileAutom, tailleEtoile);

        return etoileAutom;
    }
}