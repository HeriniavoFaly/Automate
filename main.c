#include "prototype.h"

#define MAX_LEN_FILENAME 50

/*
    taille: -taille[0] : nombre de transitions
            -taille[1] : nombre des états initiaux
            -taille[2] : nombre des états finaux
            -taille[3] : nombre des états
*/

/*----------------------MAIN -----------------------------*/

int main()
{
    char fileName[MAX_LEN_FILENAME] = "";
    Automate nouvAutomate;
    int taille[4] = {0};

    initAutomate(&nouvAutomate, taille);

    printf("Veuillez entrer le nom du fichier contenant l'automate a importer(.txt):");
    scanf("%s", fileName);

    // Nettoyer le tampon d'entrée
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

    // FILE *file = fopen("automate.txt", "r");

    FILE *file = fopen(fileName, "r");


    if(file == NULL){
        printf("On n'a pas pu trouver ce fichier dans le dossier courant. Reessayez.");
        exit(EXIT_FAILURE);
    }

    importerAutomate(&nouvAutomate, file, taille);

    fclose(file);
    printf("\nAutomate creee \n");

    menu(&nouvAutomate, taille);

    freeMemory(&nouvAutomate);

    return 0;
}


