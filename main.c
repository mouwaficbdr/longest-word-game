#include <stdio.h>
#include <string.h>
#include "fonctions.h"

int motLength(char mot[]){
    int i = 0;
    while(mot[i] != '\0'){
        i++;
    }
    return i;
}

int validationMots(char mot[]){
    FILE * fichier;


    char /*link[] = "../dico/ .txt",*/ *motDico, *result;
    // link[8] = mot[0];

    int found;

    fichier = fopen("dico.txt", "r");

    if(fichier != NULL){
        do{
            found = 0;
            result = fgets(motDico, 35 * sizeof(char), fichier);
            if(strcmp(mot, motDico) == 0){
                found = 1;
            }
        }while(found == 0 || result != NULL);
        
        if(found == 1){
            fclose(fichier);
            return motLength(mot);
        }
        fclose(fichier);
        return 0;
    }

}

int main()
{
    char mot[6] = "arbre";
    int result;
    
    // Affichage d'un message pour voir si le programme s'exécute
    printf("Test de validation du mot '%s'...\n", mot);
    
    result = validationMots(mot);

    if(result ==  0){
        printf("Le mot n'existe pas dans le dictionnaire");
    }else{
        printf("Votre score est de %d", result);
    }
    
   
   return 0;
}
