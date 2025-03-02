#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main()
{
   initialiserVariables(); 
   AImove();printf("My option is best");
   player1Score();printf("%d",3);
   player2Score();printf("%d",6);
   player1();printf("gogo");
   player2();printf("boobs");
   EntryField();printf("WASOPEDNLQ"); // Appel indispensable pour initialiser les positions
   afficherInterface();
   
   

   return 0;
}