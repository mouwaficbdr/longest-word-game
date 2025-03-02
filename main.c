#include <stdio.h>
#include <string.h>
#include "fonctions.h"



int main()
{
    char mot[6] = "arbre";
    int result;
    result = validationMots(mot);

    if(result == 0){
        printf("Le mot n'xiste pas dans le dictionnaire");
    }else{
        printf("Votre score est de %d", result);
    }
}
