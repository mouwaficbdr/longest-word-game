#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "fonctions.h"
#include <stdio.h>
#include <string.h>

int main(){
  initialiserVariables();
  afficherInterface();
  player1Score();printf("%d",scoreJoueur1);
  player2Score();printf("%d",scoreJoueur2);
  genererCaractereAleatoires();
  
  return 0;    
}
    
