#include <stdio.h>
#include <string.h>
#include "fonctions.h"



int main()
{
    char grilleDeMots[10] = {'a', 'n', 'p', 'o', 'j', 't', 'y', 'e', 'o'};
    char testMOts[10] = "atohoun", result[10];

    strcpy(result, validationChar(testMOts, grilleDeMots));
    if(result == NULL){
        printf("Le mot est incorrect");
    }else{
        printf("Le mot %s est correct", result);
    }
}