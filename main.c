#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main(){
   
    char grilles[]="hieklyovb";
     char *motL=malloc(sizeof(char)*20);
      motL=LongestWord(grilles);
    printf("%s",motL);

  return 0;    
}
    