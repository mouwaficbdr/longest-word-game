#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "fonctions.h"
#include <stdio.h>
#include <string.h>

int main(){
  // initialiserVariables();
  // afficherInterface();
  // player1Score();printf("%d",scoreJoueur1);
  // player2Score();printf("%d",scoreJoueur2);
  // genererCaractereAleatoires();
    char p1[]="Wesley", p2[]="kami";
  int tour=2,totalTour=4,numCommencer=1;  
  DemarrerPartie(p1, p2, tour, totalTour, numCommencer);
  
  return 0;    
}
    
