#include "../fonction.h/controller.h"
#include<stdio.h>
#include<string.h>


int main(){

    LongestWord("tuedjdnsp");
  MotPossible *motpos=ListeDesMots.premier;
  while(motpos!=NULL){
   printf("%s --> %d\n",motpos->mot,strlen(motpos->mot));
   motpos=motpos->suivant;
  }

  return 0;    
}
    

