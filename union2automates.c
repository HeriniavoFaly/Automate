#include "prototype.h"

bool launchUnionAutomate(Automate *autom1, int *taille1, Automate autom2, int *taille2)
{
    Automate unionAutom;
    int tailleUnion[4] = {0};

    unionAutom = unionAutomate(*autom1, taille1, autom2, taille2, tailleUnion);

    genererDotImg(&unionAutom, tailleUnion, "Automate_Union");
    if(changerAutomate())
    {
        printf("***** ON TRAVAILLE MAINTENANT AVEC L'UNION DE 2 AUTOMATES *****\n");
        copyAutomate(autom1, taille1, unionAutom, tailleUnion);
        return true;
    }
    return false;
    // freeMemory(&unionAutom);
}

Automate unionAutomate(Automate autom1, int *taille1, Automate autom2, int *taille2, int *tailleUnion)
{
    FILE *fileUnion = NULL, *fileUnionRead = NULL;
    int nouvEtatInitial = -1;
    Automate unionAutom;
    // int tailleUnion[4] = {0};

    fileUnion = fopen("unionAutom.txt", "w");
    fileUnionRead = fopen("unionAutom.txt", "r");

    if(fileUnion != NULL && fileUnionRead != NULL)
    {
        int i;
        for (i = 0; i < taille1[0]; i++)
            fprintf(fileUnion, "%d %d %s\n", autom1.transition[i].E_depart->number, autom1.transition[i].E_arrive->number, autom1.transition[i].etiquete);
        
        for (i = 0; i < taille2[0]; i++)
            fprintf(fileUnion, "%d %d %s\n", autom2.transition[i].E_depart->number, autom2.transition[i].E_arrive->number, autom2.transition[i].etiquete);
        
        for(i=0; i < taille1[1]; i++)
            fprintf(fileUnion, "%d %d %s\n", nouvEtatInitial, autom1.etatInitiaux[i], "`");

        for (i = 0; i < taille2[1]; i++)
            fprintf(fileUnion, "%d %d %s\n", nouvEtatInitial, autom2.etatInitiaux[i], "`");

        fprintf(fileUnion, ">\n");
        //etat initial
        fprintf(fileUnion, "%d\n", nouvEtatInitial);

        //etats finaux
        for (i = 0; i < taille1[2]; i++)
            fprintf(fileUnion, "%d ", autom1.etatFinaux[i]);

        for (i = 0; i < taille2[2]; i++)
            fprintf(fileUnion, "%d ", autom2.etatFinaux[i]);     
        
        fclose(fileUnion);

        initAutomate(&unionAutom, tailleUnion);
        importerAutomate(&unionAutom, fileUnionRead, tailleUnion);
        fclose(fileUnionRead);

        // automateSansEpsilone(&unionAutom, tailleUnion);

        return unionAutom;
    }
    
}
