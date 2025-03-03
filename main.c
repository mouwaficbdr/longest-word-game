#include <stdio.h>
#include <string.h>
#include "fonctions.h"



int main()
{
   char mot[6] = "arbre";
   int result;
   
   // Affichage d'un message pour voir si le programme s'exécute
   printf("Test de validation du mot '%s'...\n", mot);
   
   result = validationMots(mot);

   if(result == 0){
      printf("Le mot n'existe pas dans le dictionnaire\n");
   }else{
      printf("Votre score est de %d\n", result);
   }
   
   // Ajout d'une pause pour voir le résultat
   printf("Appuyez sur Entrée pour continuer...");
   getchar();
   
   return 0;
}
