#include "prototype.h"

void afficherAutomate(Automate *autom, int *taille)
{   
    affEtatInitiaux(autom, taille);

    affEtatFinaux(autom, taille);
        
    affTransitions(autom, taille);

    afficherAlphabet(autom);
}

void affEtatInitiaux(Automate *autom, int *taille)
{
    printf("Les etats initiaux :");
    for (int i = 0; i < taille[1]; i++)
    {
        printf("-%d", (*autom).etatInitiaux[i]);
    }
}

void affEtatFinaux(Automate *autom, int *taille)
{
    printf("\n\nLes etats finaux: ");
    for (int k = 0; k < taille[2]; k++)
    {
        printf("-%d", (*autom).etatFinaux[k]);
    }
}

void affTransitions(Automate *autom, int *taille)
{
    printf("\n\nLes transtions: \n\n");
    printf("%-20s %-20s %-20s", "E_depart", "E_arrive", "etiquette");

    for (int j = 0; j < taille[0]; j++)
    {
        printf("\n%-20d %-20d %-20s", (*autom).transition[j].E_depart->number, (*autom).transition[j].E_arrive->number, (*autom).transition[j].etiquete);
    }  
}

void afficherAlphabet(Automate *autom)
{
    printf("\nLes aphabets utilises sont: A = {");
    for (int i = 1; i < strlen((*autom).alphabet); i++)
    {
        if(i!=1)
            printf(",%c", (*autom).alphabet[i]);
        else
            printf("%c", (*autom).alphabet[i]);
    }

    printf("}\n");
    
}

void menu(Automate *autom, int *taille)
{
    char choix;

    while(choix != 'q' && choix != 'Q')
    {
        printf("\nx--------------------------------------------------------------x\n");
        printf("\n\tMENU:\n\t-afficher automate detaillee(1)\n\t-afficher alphabet(a)\n\t-generer le graphe en.png(g)\n\t-afficher l'accessibilite des etats(x)\n\t-Tester si un mot est genere par l'automate(t)\n\t-Tester les mots d'un fichier(f)\n\t-quitter(q)\n");
        printf("\nEntrez votre choix:");
        choix = getchar();

        // Nettoyer le tampon d'entrée
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch(choix)
        {
            case '1':
                afficherAutomate(autom, taille);
                break;

            case 'a':
            case 'A':
                afficherAlphabet(autom);
                break;

            case 'q':
            case 'Q':
                printf("\nQuitter...");
                break;
            case 'g':
            case 'G':
                genererDotImg(autom, taille);
                break;

            case 'x':
            case 'X':
                printf("\n");
                for (int i = 0; i < taille[3]; i++)
                {
                    printf("Etat: %d -- accessible: %d\n", autom->lesEtats[i].number, autom->lesEtats[i].accessible);
                }
                printf("\nNB: 1 = accessible, 0 = inaccessible\n");
                break;

            case 't':
            case 'T':
                char mot[] = "";
                bool isGeneratedBy = false;
                printf("\n Entrer le mot a tester : ");
                scanf("%s", mot);
                while ((getchar())!='\n');
                
                clock_t debut = clock();

                // estIlEngendre(autom, mot, taille, autom->etatInitiaux, taille[1], &isGeneratedBy);
                isGeneratedBy =  estEngendre(mot, autom, taille);

                clock_t fin = clock();

                printf("Execution time: %lf\n", (double)(fin-debut)/CLOCKS_PER_SEC);

                if(isGeneratedBy)
                    printf("\t\n\n%s est genere par l'automate.\n", mot);
                else
                {
                    // system("cls");
                    printf("\n\n\t%s n'est pas engendre par l'automate\n", mot);
                }

                break;
            
            case 'f':
            case 'F':
                clock_t debut1 = clock();

                testerMotsDansFichier(autom, taille);

                clock_t fin1 = clock();

                printf("Execution time: %.3lf\n", (double)(fin1-debut1)/CLOCKS_PER_SEC);
                break;

            default:
                printf("\nChoix invalide...");
                break;
        }
    }

}