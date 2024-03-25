// #include "prototype.h"

// //pour vérifier si l'un des derniers états fils est un état final
// bool cmpLastStates(Automate *autom, int *taille, int *lastStates, int lenLastStates)
// {
//     for(int i=0; i<taille[2]; i++)
//     {
//         for (int j = 0; j < lenLastStates; j++)
//         {
//             if (lastStates[j] == autom->etatFinaux[i])
//             {
//                 printf("Mot trouve. Etat d'acceptation: %d\n", autom->etatFinaux[i]);
//                 return true;
//             }
//         }

//     }
//     return false;
// }

// //pour trouver avoir le reste du mot après avoir pris le premier lettre
// void remainingWord(char* mot, char *reste)
// {
//     int len = (strlen(mot) < 1)? 1 : strlen(mot); // s'il ne reste qu'une caractère dans notre mot alors on va le reduire à une chaîne de fin de caractère
 
//     for (int i = 0; i < len-1; i++)
//     {
//         reste[i] = mot[i+1];
//     }
//     reste[len-1] = '\0';
// }

// void estIlEngendre(Automate *autom, char *mot, int *taille, int *EDep, int tailleT, bool *isGeneretedBy) //EDep : tableau contenant tous les états possibles de même niveau. Initialement les états initiaux; isGeneretedBy est initialisé à false
// {
//     int tailleTabTemp = 0;
//     int *temp = NULL;
//     char resteMot[strlen(mot)]; // à chaque entré on va initialisé la longueur de la chaîne par la longueur du mot courant car on a besoin d'un caractère de plus pour '\0' 

//     for(int i=0; (i<tailleT) && !(*isGeneretedBy); i++)
//     {    
//         tailleTabTemp = 0;
//         bool isTransEpsilon = false; 
//         // printf("\n");
//         for(int j=0; j<taille[0] ; j++)
//         {
//             /*
//             il faut que E_depart soit true(parcouru) pour mettre les E_arrive dans le tableau temp(ou EDep),càd parcourir l'état fils: tableau des états de même niveau à partir d'un état de départ EDep[i]
//             */ 
//             if(autom->transition[j].E_depart->number == EDep[i])
//             {  
//                 isTransEpsilon = false;
//                 if(strcmp(autom->transition[j].etiquete, "`") == 0)
//                     isTransEpsilon = true;

//                 for (int k = 0; k < strlen(autom->transition[j].etiquete); k++)
//                 {    
//                     if(mot[0] == autom->transition[j].etiquete[k] || isTransEpsilon)
//                     {
//                         temp =  (int*)realloc(temp, (++tailleTabTemp)*sizeof(int));
//                         temp[tailleTabTemp-1] = autom->transition[j].E_arrive->number;                      
//                     }
//                 }
                
//             }
//         }

//         if(tailleTabTemp != 0)
//         {
//             printf("\nmot =(%d, %s)\n",EDep[i], mot);
//             if(!isTransEpsilon)
//                 remainingWord(mot, resteMot);
            
//             if(resteMot[0]) // pour tester si le resteMot != '\0' si oui appel de fonction sinon on va aller à else 
//             {
//                 estIlEngendre(autom, resteMot, taille, temp, tailleTabTemp, isGeneretedBy); //temp: nouveau EDep
//             }              
//             else
//             {
//                 *isGeneretedBy = cmpLastStates(autom, taille, temp, tailleTabTemp);
//                 if(*isGeneretedBy)
//                     break;
//             }
//         }      
//     }
//     free(temp);
//     printf("x------x------x");
// }

// void testerMotsDansFichier(Automate *autom,  int *taille)
// {
//     char **motsEngeres= NULL;
//     char buffer[__MAX_NOMBRE_ALPHABET__];
//     int nbMotsEngedres = 0;
//     bool isGeneratedBy = false;
//     FILE *file = fopen("mots.txt", "r");

//     if(file == NULL)
//     {
//         printf("Fichier non trouvé.");
//         exit(EXIT_FAILURE);
//     }

//     while (!feof(file))
//     {
//         isGeneratedBy = false;
//         fscanf(file, "%s", buffer);

//         estIlEngendre(autom, buffer, taille, autom->etatInitiaux, taille[1], &isGeneratedBy);
//         // isGeneratedBy =  estEngendre(buffer, autom, taille);
//         system("cls");

//         if(isGeneratedBy)
//         {
//             motsEngeres = (char**)realloc(motsEngeres, (++nbMotsEngedres)*sizeof(char*));

//             motsEngeres[nbMotsEngedres - 1] = (char*)malloc((strlen(buffer))*sizeof(char));

//             strcpy(motsEngeres[nbMotsEngedres-1], buffer);
//         }    
        
//     }

//     if(nbMotsEngedres != 0)
//     {
//         printf("\nLes mots engedres par l'automate sont:\n");
//         for (int i = 0; i < nbMotsEngedres; i++)
//             printf("\t-%s\n", motsEngeres[i]);
//     }
//     else
//         printf("\nAucun des ces mots est engedre par l'automate.\n");
    

//     fclose(file);
//     free(motsEngeres);
// }