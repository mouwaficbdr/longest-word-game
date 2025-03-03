#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main()
{
    initialiserVariables();
   char word[10]="gogo";
   char mot[10]="boobs";
//    initialiserVariables(); 
   afficherInterface();
   

   AImove();printf("My option is best");
   player1Score();printf("%d",3);
   player2Score();printf("%d",6);
   centerword1(word);
   centerword2(mot);
   namePlay1();printf("kokou");
   namePlay2();printf("Robert");
//    player1();printf("gogo");
//    player2();printf("boobs");
   EntryField();printf("WASOPEDNLQ"); // Appel indispensable pour initialiser les positions
   
//    rectangle((width-(7*width/9))/2,(height-(7*height/9))/2,7*width/9,7*height/9);
//    rectangle(frameX,frameY,frameLong,frameHeight);
//    rectangle(scorefieldX1,scorefieldY1,scorefieldLong,scorefieldHeight);
//    rectangle(scorefieldX2,scorefieldY2,scorefieldLong,scorefieldHeight);
//    rectangle(mainframeX,mainframeY,mainframeLong,mainframeHeight);
//    printf("\n\n");

   return 0;
}