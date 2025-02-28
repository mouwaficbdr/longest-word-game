#include <stdio.h>
#include <stdlib.h>
#include "fonctions.c"


int main(){
   
    char grilles[]="batudtfejh";
    char *motL=malloc(sizeof(char)*20);
     motL=LongestWord(grilles);
   printf("%s",motL);

  return 0;
}
    